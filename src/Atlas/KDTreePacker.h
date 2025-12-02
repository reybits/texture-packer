/**********************************************\
*
*  Andrey A. Ugolnik
*  http://www.ugolnik.info
*  andrey@ugolnik.info
*
\**********************************************/

#pragma once

#include "AtlasPacker.h"

#include <vector>

class cKDNode;

class KDTreePacker final : public AtlasPacker
{
public:
    explicit KDTreePacker(const sConfig& config);
    ~KDTreePacker() override;

    static bool Compare(const cImage* a, const cImage* b);

    void setSize(const sSize& size) override;
    bool add(const cImage* image) override;
    void makeAtlas(bool overlay) override;

    uint32_t getRectsCount() const override;
    const cImage* getImageByIndex(uint32_t idx) const override;
    const sRect& getRectByIndex(uint32_t idx) const override;

private:
    cKDNode* m_root = nullptr;

    struct sPiece
    {
        const cImage* image;
        cKDNode* node;
    };
    std::vector<sPiece> m_nodes;
};
