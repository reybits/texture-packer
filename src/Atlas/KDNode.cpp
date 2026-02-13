/**********************************************\
*
*  Andrey A. Ugolnik
*  http://www.ugolnik.info
*  andrey@ugolnik.info
*
\**********************************************/

#include "KDNode.h"

cKDNode::cKDNode(const sRect& area, uint32_t padding)
    : m_area(area)
    , m_padding(padding)
{
}

cKDNode::~cKDNode()
{
    delete m_childA;
    delete m_childB;
}

cKDNode* cKDNode::add(const sSize& size)
{
    if (isLeaf())
    {
        // end of the tree, no more room
        if (m_used)
        {
            return nullptr;
        }

        const auto padding = m_padding;

        const auto imgWidth = size.width + padding * 2;
        const auto imgHeight = size.height + padding * 2;

        const auto nodeWidth = m_area.width();
        const auto nodeHeight = m_area.height();

        const auto x = m_area.left;
        const auto y = m_area.top;
        m_rect = { x, y, x + size.width, y + size.height };

        // size matches exactly
        if (imgWidth == nodeWidth && imgHeight == nodeHeight)
        {
            m_used = true;
            return this;
        }

        // rect is too big for this node
        if (imgWidth > nodeWidth || imgHeight > nodeHeight)
        {
            return nullptr;
        }

        // split this node in two
        const auto subwidth = nodeWidth - imgWidth;
        const auto subheight = nodeHeight - imgHeight;

        if (subwidth <= subheight)
        {
            // split --
            m_childA = new cKDNode({ x, y, x + nodeWidth, y + imgHeight }, padding);
            m_childB = new cKDNode({ x, y + imgHeight, x + nodeWidth, y + imgHeight + subheight }, padding);
        }
        else
        {
            // split |
            m_childA = new cKDNode({ x, y, x + imgWidth, y + nodeHeight }, padding);
            m_childB = new cKDNode({ x + imgWidth, y, x + imgWidth + subwidth, y + nodeHeight }, padding);
        }

        return m_childA->add(size);
    }
    else if (m_childA != nullptr)
    {
        auto node = m_childA->add(size);
        if (node != nullptr)
        {
            return node;
        }
        else if (m_childB != nullptr)
        {
            return m_childB->add(size);
        }
    }

    return nullptr;
}
