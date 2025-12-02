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
            shiftArg(argc, argv, i, outputAtlasName);
        }
        else if (::strcmp(arg, "-res") == 0) // FIXME: deprecated, remove after 2025.02.30
        {
            deprecatedOption(arg, "--res", "2025.02.30");
            shiftArg(argc, argv, i, outputResName);
        }
        else if (::strcmp(arg, "--res") == 0)
        {
            shiftArg(argc, argv, i, outputResName);
        }
        else if (::strcmp(arg, "-prefix") == 0) // FIXME: deprecated, remove after 2025.02.30
        {
            deprecatedOption(arg, "--prefix", "2025.02.30");
            shiftArg(argc, argv, i, resPathPrefix);
        }
        else if (::strcmp(arg, "--prefix") == 0)
        {
            shiftArg(argc, argv, i, resPathPrefix);
        }
        else if (::strcmp(arg, "-b") == 0)
        {
            shiftArg(argc, argv, i, config.border);
        }
        else if (::strcmp(arg, "-p") == 0)
        {
            shiftArg(argc, argv, i, config.padding);
        }
        else if (::strcmp(arg, "-max") == 0) // FIXME: deprecated, remove after 2025.02.30
        {
            deprecatedOption(arg, "--max", "2025.02.30");
            shiftArg(argc, argv, i, config.maxTextureSize);
        }
        else if (::strcmp(arg, "--max") == 0)
        {
            shiftArg(argc, argv, i, config.maxTextureSize);
        }
        else if (::strcmp(arg, "-tl") == 0) // FIXME: deprecated, remove after 2025.02.30
        {
            deprecatedOption(arg, "--trim-name", "2025.02.30");
            shiftArg(argc, argv, i, trimCount);
        }
        else if (::strcmp(arg, "--trim-name") == 0)
        {
            shiftArg(argc, argv, i, trimCount);
        }
        else if (::strcmp(arg, "-pot") == 0) // FIXME: deprecated, remove after 2025.02.30
        {
            deprecatedOption(arg, "--pot", "2025.02.30");
            config.pot = true;
        }
        else if (::strcmp(arg, "--pot") == 0)
        {
            config.pot = true;
        }
        else if (::strcmp(arg, "--multi") == 0)
        {
            config.multi = true;
        }
        else if (::strcmp(arg, "-trim") == 0) // FIXME: deprecated, remove after 2025.02.30
        {
            deprecatedOption(arg, "--trim", "2025.02.30");
            config.trim = true;
        }
        else if (::strcmp(arg, "--trim") == 0)
        {
            config.trim = true;
        }
        else if (::strcmp(arg, "-dupes") == 0) // FIXME: deprecated, remove after 2025.02.30
        {
            deprecatedOption(arg, "--dupes", "2025.02.30");
            config.alowDupes = true;
        }
        else if (::strcmp(arg, "--dupes") == 0)
        {
            config.alowDupes = true;
        }
        else if (::strcmp(arg, "-slow") == 0) // FIXME: deprecated, remove after 2025.02.30
        {
            deprecatedOption(arg, "--classic-packing", "2025.02.30");
            config.slowMethod = true;
        }
        else if (::strcmp(arg, "--classic-packing") == 0)
        {
            config.slowMethod = true;
        }
        else if (::strcmp(arg, "-dropext") == 0) // FIXME: deprecated, remove after 2025.02.30
        {
            deprecatedOption(arg, "--drop-ext", "2025.02.30");
            config.dropExt = true;
        }
        else if (::strcmp(arg, "--drop-ext") == 0)
        {
            config.dropExt = true;
        }
        else if (::strcmp(arg, "-overlay") == 0) // FIXME: deprecated, remove after 2025.02.30
        {
            deprecatedOption(arg, "--overlay", "2025.02.30");
            config.overlay = true;
        }
        else if (::strcmp(arg, "--overlay") == 0)
        {
            config.overlay = true;
        }
        else if (::strcmp(arg, "-nr") == 0) // FIXME: deprecated, remove after 2025.02.30
        {
            deprecatedOption(arg, "--no-recurse", "2025.02.30");
            recurse = false;
        }
        else if (::strcmp(arg, "--no-recurse") == 0)
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
    name = p != nullptr
        ? p + 1
        : name;
    cLog::Info("  {} INPUT_IMAGE [INPUT_IMAGE] <OPTIONS> -o ATLAS", name);
    cLog::Info("");
    cLog::Info("  INPUT_IMAGE        Input image file or directory (space-separated)");
    cLog::Info("  -b size            Add border around sprites (default: {} px)", config.border);
    cLog::Info("  -p size            Add padding between sprites (default: {} px)", config.padding);
    cLog::Info("  -o ATLAS           Output atlas file name (default: PNG)");
    cLog::Info("  --res DESC_TEXTURE Output atlas description as XML");
    cLog::Info("  --prefix STRING    Add prefix to texture path");
    cLog::Info("  --classic-packing  Use alternative packing algorithm (may produce better results, default: {})", isEnabled(config.slowMethod));
    cLog::Info("  --drop-ext         Remove file extension from sprite ID (default: {})", isEnabled(config.dropExt));
    cLog::Info("  --dupes            Allow duplicate sprites (default: {})", isEnabled(config.alowDupes));
    cLog::Info("  --keep-float       Preserve float hotspot coordinates (default: {})", isEnabled(config.keepFloat));
    cLog::Info("  --max size         Maximum atlas size (default: {} px)", config.maxTextureSize);
    // cLog::Info("  --multi            Enable multi-atlas output (default: {})", isEnabled(config.multi));
    cLog::Info("  --no-recurse       Do not search subdirectories");
    cLog::Info("  --overlay          Overlay sprites (default: {})", isEnabled(config.overlay));
    cLog::Info("  --pot              Make atlas dimensions power of two (default: {})", isEnabled(config.pot));
    cLog::Info("  --trim             Trim transparent borders from sprites (default: {})", isEnabled(config.trim));
    cLog::Info("  --trim-name count  Remove 'count' characters from the start of sprite IDs (default: 0)");
}
