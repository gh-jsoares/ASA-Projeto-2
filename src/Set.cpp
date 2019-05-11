#include "Set.hpp"

Edge::Edge(int flow, int capacity, std::shared_ptr<Node> node) : flow(flow), capacity(capacity), node(node) { }
Node::Node(int id) : id(id) { }

Set::Set(int num_nodes, int f) : m_num_nodes(num_nodes), m_f(f)
{
    m_adj = new std::vector<std::shared_ptr<Edge>>[num_nodes];
    m_nodes = new std::shared_ptr<Node>[num_nodes];
    for (int i = 0; i < m_num_nodes; i++) {
        int id = getNodeId(i);
        m_nodes[i] = std::make_shared<Node>(id);
    }
    
}

Set::~Set() {
    delete [] m_adj;
    delete [] m_nodes;
}

void Set::addEdge(int origin_id, int destination_id, int capacity)
{
    addEdge(origin_id, destination_id, 0, capacity);
}

void Set::addEdge(int origin_id, int destination_id, int flow, int capacity)
{
    int origin_index = getNodeIndex(origin_id);
    auto destination_node = getNode(destination_id);

    m_adj[origin_index].push_back(std::make_shared<Edge>(flow, capacity, destination_node));
}

int Set::getNodeIndex(std::shared_ptr<Node> node)
{
    return getNodeIndex(node->id);
}

int Set::getNodeIndex(int id)
{
    int index = ABS(id);

    if(isStorage(id)) {
        index += index - (m_f + 2);
        if(id < 0)
            index++;
    }

    return index;
}

int Set::getNodeId(int index)
{
    int id = index;

    if(isStorage(id)) {
        id = (id + (m_f + 2)) / 2;
        if(index < 0)
            index += 1;
    }

    return id;
}

bool Set::isStorage(std::shared_ptr<Node> node)
{
    return isStorage(node->id);
}

bool Set::isStorage(int id)
{
    return id > m_f || id < 0;
}

std::shared_ptr<Node> Set::getNode(int id)
{
    int index = getNodeIndex(id);
    return m_nodes[index];
}

void Set::createNode(int id)
{
    auto node = std::make_shared<Node>(id);
    int index = getNodeIndex(id);

    m_nodes[index] = node;
}

std::shared_ptr<Node> Set::overFlowNode()
{
    for(int i = 2; i < m_num_nodes; i++) { // 0 and 1 will have excess flow values after the algorithm
        std::shared_ptr<Node> node = m_nodes[i];
        if(node != NULL && node->excess_flow > 0)
            return node;
    }

    return nullptr;
}

void Set::preflow(std::shared_ptr<Node> origin)
{
    origin->height = m_num_nodes;

    int origin_index = getNodeIndex(origin);

    for(auto it = m_adj[origin_index].begin(); it != m_adj[origin_index].end(); ++it) {
        auto edge = (*it);
        edge->flow = edge->capacity;
        edge->node->excess_flow += edge->flow;

        addEdge(edge->node->id, origin->id, -edge->flow, 0);
    }
}

void Set::updateReverseEdgeFlow(int origin_id, int destination_id, int flow)
{
    int origin_index = getNodeIndex(destination_id);

    for(auto it = m_adj[origin_index].begin(); it != m_adj[origin_index].end(); ++it) {
        auto edge = (*it);
        if(edge->node->id == origin_id) {
            edge->flow += -flow;
            return;
        }
    }

    addEdge(destination_id, origin_id, 0, flow);
}


bool Set::push(std::shared_ptr<Node> node)
{
    int origin_index = getNodeIndex(node);

    for(auto it = m_adj[origin_index].begin(); it != m_adj[origin_index].end(); ++it) {
        auto edge = (*it);
        if(edge->flow == edge->capacity)
            continue;

        auto destination_node = edge->node;
        if(node->height > destination_node->height) {
            int flow = MIN(edge->capacity - edge->flow, node->excess_flow);
            node->excess_flow -= flow;
            destination_node->excess_flow += flow;

            edge->flow += flow;

            updateReverseEdgeFlow(node->id, destination_node->id, flow);

            return true;
        }
    }

    return false;
}

void Set::relabel(std::shared_ptr<Node> node)
{
    int minimum_height = INT_MAX;

    int origin_index = getNodeIndex(node);

    for(auto it = m_adj[origin_index].begin(); it != m_adj[origin_index].end(); ++it) {
        auto edge = (*it);
        if(edge->flow == edge->capacity)
            continue;

        auto destination_node = edge->node;
        if(destination_node->height < minimum_height) {
            minimum_height = destination_node->height;
                node->height = minimum_height + 1;
        }
    }
}

int Set::getMaxFlow()
{
    auto source = getNode(0);
    auto tail = getNode(1);
    preflow(source);

    while(overFlowNode() != nullptr) {
        auto node = overFlowNode();
        if(!push(node))
            relabel(node);
    }
    LOG("\n");
    LOG("========NODES========");
    LOG("id | height | e_flow");
    for (int i = 0; i < m_num_nodes; i++) {
        auto n = m_nodes[i];
        LOG(std::to_string(n->id) + " | "
        + std::to_string(n->height) + " | "
        + std::to_string(n->excess_flow));
    }
    LOG(" ");
    LOG("========EDGES========");
    LOG("origin | destination | capacity | flow");
    for (int i = 0; i < m_num_nodes; i++) {
        for(auto it = m_adj[i].begin(); it != m_adj[i].end(); ++it) {
            auto edge = (*it);
            int origin_id = getNodeId(i);
            int destination_id = edge->node->id;
            int capacity = edge->capacity;
            int flow = edge->flow;
            LOG(std::to_string(origin_id) + " | "
            + std::to_string(destination_id) + " | "
            + std::to_string(capacity) + " | "
            + std::to_string(flow));
        }
    }
    LOG("\n");
    return tail->excess_flow;
}