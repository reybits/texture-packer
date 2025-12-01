/**********************************************\
*
*  Andrey A. Ugolnik
*  http://www.ugolnik.info
*  andrey@ugolnik.info
*
\**********************************************/

#include "Config.h"
#include "FileList.h"
#include "ImageList.h"
#include "Log.h"
#include "Utils.h"

#include <cstdlib>
#include <cstring>
#include <string>

void showHelp(const char* name, const sConfig& config);

int main(int argc, char* argv[])
{
    sConfig config;

    cLog::Info("Texture Packer v1.3.4.");
    cLog::Info("Copyright (c) 2017-2025 Andrey A. Ugolnik.");
    cLog::Info("");
    if (argc < 3)
    {
        showHelp(argv[0], config);
        return -1;
    }

    const char* outputAtlasName = nullptr;
    const char* outputResName = nullptr;
    const char* resPathPrefix = nullptr;

    cFileList fileList;

    uint32_t trimCount = 0u;
    auto recurse = true;

    for (int i = 1; i < argc; i++)
    {
        const char* arg = argv[i];

        if (::strcmp(arg, "-o") == 0)
        {
            if (i + 1 < argc)
            {
                outputAtlasName = argv[++i];
            }
        }
        else if (::strcmp(arg, "-res") == 0)
        {
            if (i + 1 < argc)
            {
                outputResName = argv[++i];
            }
        }
        else if (::strcmp(arg, "-prefix") == 0)
        {
            if (i + 1 < argc)
            {
                resPathPrefix = argv[++i];
            }
        }
        else if (::strcmp(arg, "-b") == 0)
        {
            if (i + 1 < argc)
            {
                config.border = static_cast<uint32_t>(::atoi(argv[++i]));
            }
        }
        else if (::strcmp(arg, "-p") == 0)
        {
            if (i + 1 < argc)
            {
                config.padding = static_cast<uint32_t>(::atoi(argv[++i]));
            }
        }
        else if (::strcmp(arg, "-max") == 0)
        {
            if (i + 1 < argc)
            {
                config.maxTextureSize = static_cast<uint32_t>(::atoi(argv[++i]));
            }
        }
        else if (::strcmp(arg, "-tl") == 0)
        {
            if (i + 1 < argc)
            {
                trimCount = static_cast<uint32_t>(::atoi(argv[++i]));
            }
        }
        else if (::strcmp(arg, "-pot") == 0)
        {
            config.pot = true;
        }
        else if (::strcmp(arg, "-multi") == 0)
        {
            config.multi = true;
        }
        else if (::strcmp(arg, "-trim") == 0)
        {
            config.trim = true;
        }
        else if (::strcmp(arg, "-dupes") == 0)
        {
            config.alowDupes = true;
        }
        else if (::strcmp(arg, "-slow") == 0)
        {
            config.slowMethod = true;
        }
        else if (::strcmp(arg, "-dropext") == 0)
        {
            config.dropExt = true;
        }
        else if (::strcmp(arg, "-overlay") == 0)
        {
            config.overlay = true;
        }
        else if (::strcmp(arg, "-nr") == 0)
        {
            recurse = false;
        }
        else
        {
            fileList.addPath(trimCount, arg, recurse);
        }
    }

    if (outputAtlasName == nullptr)
    {
        cLog::Info("No output name defined.");
        return -1;
    }

    config.dump();
    if (resPathPrefix != nullptr)
    {
        cLog::Info("Resource path prefix: {}.", resPathPrefix);
    }
    cLog::Info("");

    auto startTime = getCurrentTime();

    // sort and remove dupes
    if (config.alowDupes == false)
    {
        fileList.removeDupes();
    }

    // load images
    auto& files = fileList.getList();
    cImageList imageList(config, files.size());

    for (const auto& f : files)
    {
        auto image = imageList.loadImage(f.path, f.trimCount);
        if (image == nullptr)
        {
            cLog::Warning("File '{}' not loaded.", f.path);
        }
    }

    auto& images = imageList.getList();

    cLog::Info("Loaded {} ({}) images in {:.2f} ms.",
               static_cast<uint32_t>(images.size()),
               static_cast<uint32_t>(files.size()),
               (getCurrentTime() - startTime) * 0.001f);

    // packing
    sSize atlasSize;
    if (imageList.doPacking(outputAtlasName, outputResName, resPathPrefix, atlasSize) == false)
    {
        cLog::Info("");
        cLog::Info("Desired texture size {} x {}, but maximum {} x {}.",
                   atlasSize.width, atlasSize.height,
                   config.maxTextureSize, config.maxTextureSize);

        return -1;
    }

    return 0;
}

void showHelp(const char* name, const sConfig& config)
{
    cLog::Info("Usage:");
    auto p = ::strrchr(name, '/');
    cLog::Info("  {} INPUT_IMAGE [INPUT_IMAGE] -o ATLAS", p ? p + 1 : name);
    cLog::Info("");
    cLog::Info("  INPUT_IMAGE        input image name or directory separated by space");
    cLog::Info("  -o ATLAS           output atlas name (default PNG)");
    cLog::Info("  -res DESC_TEXTURE  output atlas description as XML");
    cLog::Info("  -prefix STRING     add prefix to texture path");
    cLog::Info("  -pot               make power of two atlas (default {})", isEnabled(config.pot));
    cLog::Info("  -nr                don't recurse in next directory");
    cLog::Info("  -tl count          trim left sprite's id by count (default 0)");
    cLog::Info("  -multi             enable multi-atlas (default {})", isEnabled(config.multi));
    cLog::Info("  -trim              trim sprites (default {})", isEnabled(config.trim));
    cLog::Info("  -overlay           overlay sprites (default {})", isEnabled(config.overlay));
    cLog::Info("  -dupes             allow dupes (default {})", isEnabled(config.alowDupes));
    cLog::Info("  -slow              use slow method instead kd-tree (default {})", isEnabled(config.slowMethod));
    cLog::Info("  -b size            add border around sprites (default {} px)", config.border);
    cLog::Info("  -p size            add padding between sprites (default {} px)", config.padding);
    cLog::Info("  -dropext           drop file extension from sprite id (default {})", isEnabled(config.dropExt));
    cLog::Info("  -max size          max atlas size (default {} px)", config.maxTextureSize);
}
