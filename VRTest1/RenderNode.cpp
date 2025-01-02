
#include "RenderNode.h"

RenderNode::RenderNode(RenderableObject* obj) : info(obj), link(nullptr) {

}

RenderNode::RenderNode(RenderableObject* obj, RenderNode* link) : info(obj), link(link) {

}

RenderableObject* RenderNode::getInfo()
{
	return this->info;
}

RenderNode* RenderNode::getLink()
{
	return this->link;
}

void RenderNode::setLink(RenderNode* node)
{
	this->link = node;
}
