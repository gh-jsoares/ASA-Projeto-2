#include "Network.hpp"

Edge::Edge(int flow, int capacity, std::shared_ptr<Node> node, std::shared_ptr<Node> origin)
    : flow(flow), capacity(capacity), node(node), origin(origin) { }

Node::Node(int id) : id(id) { }

Path::Path(int id_1, int id_2) : id_1(id_1), id_2(id_2) { }

Network::Network(int num_nodes, int f) : m_num_nodes(num_nodes), m_f(f)
{
    m_adj = new std::vector<std::shared_ptr<Edge>>[num_nodes];
    m_adj_relative = new std::vector<std::shared_ptr<Edge>>[num_nodes];

    m_nodes = new std::shared_ptr<Node>[num_nodes];
    for (int i = 0; i < m_num_nodes; i++) {
        int id = getNodeId(i);
        m_nodes[i] = std::make_shared<Node>(id);
    }
    
}

Network::~Network() {
    delete [] m_adj;
    delete [] m_adj_relative;
    delete [] m_nodes;
}

void Network::addEdge(int origin_id, int destination_id, int capacity)
{
    int origin_index = getNodeIndex(origin_id);
    auto destination_node = getNode(destination_id);
    auto origin_node = getNode(origin_id);

    auto edge = std::make_shared<Edge>(0, capacity, destination_node, origin_node);
    m_adj[origin_index].push_back(edge);

    m_adj_relative[origin_index].push_back(edge);
}

std::shared_ptr<Edge> Network::addEdge(int origin_id, int destination_id, int flow, int capacity)
{
    int origin_index = getNodeIndex(origin_id);
    auto destination_node = getNode(destination_id);
    auto origin_node = getNode(origin_id);

    auto edge = std::make_shared<Edge>(flow, capacity, destination_node, origin_node);
    m_adj_relative[origin_index].push_back(edge);

    return edge;
}

int Network::getNodeIndex(std::shared_ptr<Node> node)
{
    return getNodeIndex(node->id);
}

int Network::getNodeIndex(int id)
{
    int index = ABS(id);

    if(isStorage(id)) {
        index += index - (m_f + 2);
        if(id < 0)
            index++;
    }

    return index;
}

int Network::getNodeId(int index)
{
    int id = index;

    if(isStorage(id)) {
        id = (id + (m_f + 2)) / 2;
        if((m_f % 2 != 0 && index % 2 == 0) || (m_f % 2 == 0 && index % 2 != 0))
            id *= -1;
    }

    return id;
}

bool Network::isStorage(std::shared_ptr<Node> node)
{
    return isStorage(node->id);
}

bool Network::isStorage(int id)
{
    return id > m_f + 1 || id < 0;
}

std::shared_ptr<Node> Network::getNode(int id)
{
    int index = getNodeIndex(id);
    return m_nodes[index];
}

std::shared_ptr<Node> Network::overFlowNode()
{
    for(int i = 2; i < m_num_nodes; i++) { // 0 and 1 will have excess flow values after the algorithm
        std::shared_ptr<Node> node = m_nodes[i];
        if(node->excess_flow > 0)
            return node;
    }

    return nullptr;
}

void Network::preflow(std::shared_ptr<Node> origin)
{
    origin->height = m_num_nodes;

    int origin_index = getNodeIndex(origin);

    for(auto it = m_adj_relative[origin_index].begin(); it != m_adj_relative[origin_index].end(); ++it) {
        auto edge = (*it);
        edge->flow = edge->capacity;
        edge->node->excess_flow = edge->capacity;

        addEdge(edge->node->id, origin->id, -edge->flow, 0);
    }
}

void Network::updateReverseEdgeFlow(int origin_id, int destination_id, int flow)
{
    int origin_index = getNodeIndex(destination_id);

    for(auto it = m_adj_relative[origin_index].begin(); it != m_adj_relative[origin_index].end(); ++it) {
        auto edge = (*it);
        if(edge->node->id == origin_id) {
            edge->flow -= flow;
            return;
        }
    }

    addEdge(destination_id, origin_id, 0, flow);
}


bool Network::push(std::shared_ptr<Node> node)
{
    int origin_index = getNodeIndex(node);

    for(auto it = m_adj_relative[origin_index].begin(); it != m_adj_relative[origin_index].end(); ++it) {
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

void Network::relabel(std::shared_ptr<Node> node)
{
    int minimum_height = INT_MAX;

    int origin_index = getNodeIndex(node);

    for(auto it = m_adj_relative[origin_index].begin(); it != m_adj_relative[origin_index].end(); ++it) {
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

void Network::debug()
{
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
        for(auto it = m_adj_relative[i].begin(); it != m_adj_relative[i].end(); ++it) {
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
}

int Network::getMaxFlow()
{
    auto source = getNode(0);
    auto tail = getNode(1);
    preflow(source);

    while(overFlowNode() != nullptr) {
        auto node = overFlowNode();
        if(!push(node))
            relabel(node);
    }

    // debug();

    return tail->excess_flow;
}

void Network::DFS()
{
    bool *visited = new bool[m_num_nodes];

    for(int i = 0; i < m_num_nodes; i++)
        visited[i] = false;

    DFSUtil(1, visited);

    std::vector<int> storages;
    std::vector<std::shared_ptr<Path>> paths;

    for(int i = 1; i < m_num_nodes; i++) {
        if(!visited[i])
            for(auto it = m_adj_relative[i].begin(); it != m_adj_relative[i].end(); ++it) {
                auto edge = (*it);
                int other_index = getNodeIndex(edge->node);
                if(visited[other_index]) {
                    int id_1 = ABS(getNodeId(i));
                    int id_2 = ABS(getNodeId(other_index));
                    if(id_1 == id_2) // storage
                        storages.push_back(id_1);
                    else { // path
                        auto path = std::make_shared<Path>(id_1, id_2);
                        paths.push_back(path);
                    }
                }
            }
    }
    
    std::sort(storages.begin(), storages.end());
    for(auto it2 = storages.begin(); it2 != storages.end(); ++it2) {
        if(it2 != storages.begin())
            printf(" ");
        printf("%d", (*it2));
    }
    printf("\n");

    std::sort(paths.begin(), paths.end(), [](const std::shared_ptr<Path>& p1, const std::shared_ptr<Path>& p2)
    {
        return std::tie(p1->id_1, p1->id_2) < std::tie(p2->id_1, p2->id_2);
    });

    for(auto it2 = paths.begin(); it2 != paths.end(); ++it2) {
        printf("%d %d\n", (*it2)->id_1, (*it2)->id_2);
    }

    delete [] visited;
}

std::shared_ptr<Edge> Network::getEdge(int origin_index, int destination_index)
{
    for(auto it = m_adj_relative[origin_index].begin(); it != m_adj_relative[origin_index].end(); ++it) {
        auto edge = (*it);
        int other_index = getNodeIndex(edge->node);
        if(other_index == destination_index)
            return edge;
    }
    return nullptr;
}

void Network::DFSUtil(int index, bool *visited)
{
    visited[index] = true;

    for(int u = 0; u < m_num_nodes; u++) {
        auto edge = getEdge(u, index);
        if(!visited[u] && edge != nullptr && edge->capacity - edge->flow > 0)
            DFSUtil(u, visited);
    }
}