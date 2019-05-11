#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <bits/stdc++.h>

#define TYPE_SUPPLIER 0
#define TYPE_STORAGE 1

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define ABS(a) ((a) < 0 ? -(a) : (a))

struct Path
{
    int id_1;
    int id_2;
    Path(int id_1, int id_2);
};

struct Node
{
    int id;
    int excess_flow = 0;
    int height = 0;

    Node(int id);
};

struct Edge
{
    int flow;
    int capacity;
    std::shared_ptr<Node> node;

    std::shared_ptr<Node> origin;

    Edge(int flow, int capacity, std::shared_ptr<Node> node, std::shared_ptr<Node> origin);
};

class Network
{
private:
    int m_num_nodes;
    int m_f; // num suppliers

    std::vector<std::shared_ptr<Edge>> *m_adj;
    std::vector<std::shared_ptr<Edge>> *m_adj_relative;
    std::shared_ptr<Node> *m_nodes; // available nodes
    std::vector<std::shared_ptr<Edge>> m_increases; // what should change

    std::shared_ptr<Edge> addEdge(int origin_id, int destination_id, int flow, int capacity);

    int getNodeIndex(std::shared_ptr<Node> node);
    int getNodeIndex(int id);

    int getNodeId(int index);

    bool isStorage(std::shared_ptr<Node> node);

    std::shared_ptr<Node> getNode(int id);

    // relabel
    std::shared_ptr<Node> overFlowNode();
    void preflow(std::shared_ptr<Node> origin);
    void updateReverseEdgeFlow(int origin_id, int destination_id, int flow);
    bool push(std::shared_ptr<Node> node);
    void relabel(std::shared_ptr<Node> node);

    // dfs
    void DFSUtil(int index, bool *visited);

    std::shared_ptr<Edge> getEdge(int origin_index, int destination_index);
public:
    Network(int num_nodes, int f);
    ~Network();

    void addEdge(int origin_id, int destination_id, int capacity);

    bool isStorage(int id);

    int getMaxFlow();

    void DFS();
};

class Parser
{
private:
    std::string read_line();
    std::string read_three_num_line(int *a, int *b, int *c);
    int cycle_line(std::string line, Network *network, int type, int num_nodes, int num_elements);
public:
    Network factory();
};

class Writer
{
public:
    Writer();
    void write(Network *network);
};

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
    unsigned int i = 0;
    printf("%d", storages[i]);
    for(i = 1; i < storages.size(); i++) {
        printf(" %d", storages[i]);
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

std::string Parser::read_line() {
    std::string line;
    std::getline(std::cin, line);
    return line;
}

std::string Parser::read_three_num_line(int *a, int *b, int *c)
{
    std::string line = read_line();
    sscanf(line.c_str(), "%d %d %d", a, b, c);
    return line;
}

int Parser::cycle_line(std::string line, Network *network, int type, int num_nodes, int num_elements)
{
    char *tmp = new char[line.length() + 1];
    strcpy(tmp, line.c_str());

    int n;
    for(int i = 0; i < num_elements; i++) {
        sscanf(tmp, "%d %[^\n]", &n, tmp);
        num_nodes++;
        if(type == TYPE_SUPPLIER)
            network->addEdge(0, num_nodes , n);
        else
            network->addEdge(num_nodes, -num_nodes , n);
    }

    delete [] tmp;
    
    return num_nodes;
}

Network Parser::factory() {
    std::string line;
    int num_suppliers, num_storages, num_connections;

    line = read_three_num_line(&num_suppliers, &num_storages, &num_connections);
    Network network(num_suppliers + num_storages * 2 + 2, num_suppliers);;

    int num_nodes = 1;

    line = read_line();
    num_nodes = cycle_line(line, &network, TYPE_SUPPLIER, num_nodes, num_suppliers);

    line = read_line();
    num_nodes = cycle_line(line, &network, TYPE_STORAGE, num_nodes, num_storages);

    int origin_id, destination_id, capacity;
    for(int i = 0; i < num_connections; i++ ) {
        line = read_three_num_line(&origin_id, &destination_id, &capacity);

        if(network.isStorage(origin_id))
            origin_id *= -1; // storages are paths between 2 nodes with symmetrical ids

        network.addEdge(origin_id, destination_id, capacity);
    }
    
    return network;
}

void Writer::write(Network *network)
{
    printf("%d\n", network->getMaxFlow());

    network->DFS();
}

int main()
{
    Parser parser;
    Writer writer;

    Network network = parser.factory();

    writer.write(&network);

    return 0;
}