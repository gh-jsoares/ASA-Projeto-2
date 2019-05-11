#include "Graph.hpp"

Graph::Graph(int num_vertices, int num_suppliers)
    : m_num_vertices(num_vertices), m_num_suppliers(num_suppliers) {
    auto source = std::make_shared<Node>(0);
    addNode(source);
}

void Graph::addNode(std::shared_ptr<Node> node)
{
    m_nodes.push_back(node);
    m_num_vertices++;
}

void Graph::addConnection(std::shared_ptr<Node> origin, std::shared_ptr<Node> destination, int capacity)
{
    auto connection = std::make_shared<Connection>(0, capacity, origin, destination);
    m_connections.push_back(connection);
}

void Graph::preflow(std::shared_ptr<Node> origin)
{
    origin->setHeight(m_num_vertices);

    for(unsigned int i = 0; i < m_connections.size(); i++) {
        auto connection = m_connections[i];
        if(connection->getOrigin() == origin) {
            connection->setFlow(connection->getCapacity());

            connection->getDestination()->addExcessFlow(connection->getFlow());

            auto residual_connection = std::make_shared<Connection>(-connection->getFlow(), 0, connection->getDestination(), origin);
            m_connections.push_back(residual_connection);
        }
    }
}

std::shared_ptr<Node> Graph::overFlowNode()
{
    for(int i = 1; i < m_num_vertices - 1; i++) {
        auto node = m_nodes[i];
        if(node->getExcessFlow() > 0)
            return node;
    }

    return nullptr;
}

void Graph::updateReverseEdgeFlow(std::shared_ptr<Connection> connection, int flow)
{
    auto origin = connection->getDestination();
    auto destination = connection->getOrigin();

    for(unsigned int i = 0; i < m_connections.size(); i++) {
        auto current_connection = m_connections[i];
        if(current_connection->getDestination() == destination && current_connection->getOrigin() == origin) {
            current_connection->addFlow(-flow);
            return;
        }
    }

    auto residual_connection = std::make_shared<Connection>(0, flow, origin, destination);
    m_connections.push_back(residual_connection);
}

bool Graph::push(std::shared_ptr<Node> node)
{
    for(unsigned int i = 0; i < m_connections.size(); i++) {
        auto connection = m_connections[i];
        auto origin = connection->getOrigin();
        if(origin == node) {
            if(connection->getFlow() == connection->getCapacity())
                continue;

            auto destination = connection->getDestination();
            if(node->getHeight() > destination->getHeight()) {
                int flow = MIN(connection->getCapacity() - connection->getFlow(), node->getExcessFlow());
                node->addExcessFlow(-flow);
                destination->addExcessFlow(flow);

                connection->addFlow(flow);

                updateReverseEdgeFlow(connection, flow);

                return true;
            }
        }
    }

    return false;
}

void Graph::relabel(std::shared_ptr<Node> node)
{
    int minimum_height = INT_MAX;

    for(unsigned int i = 0; i < m_connections.size(); i++) {
        auto connection = m_connections[i];
        if(connection->getOrigin() == node) {
            if(connection->getFlow() == connection->getCapacity())
                continue;
            
            auto destination = connection->getDestination();
            if(destination->getHeight() < minimum_height) {
                minimum_height = destination->getHeight();
                node->setHeight(minimum_height + 1);
            }
        }
    }
}

int Graph::getMaxFlow()
{
    preflow(getSource());

    while(overFlowNode() != nullptr) {
        auto node = overFlowNode();
        if(!push(node))
            relabel(node);
    }
    // LOG("\n");
    // LOG("========NODES========");
    // LOG("id | height | e_flow");
    // for (int i = 0; i < m_num_vertices; i++) {
    //     auto n = m_nodes[i];
    //     LOG(std::to_string(n->getId()) + " | "
    //     + std::to_string(n->getHeight()) + " | "
    //     + std::to_string(n->getExcessFlow()));
    // }
    // LOG(" ");
    // LOG("========EDGES========");
    // LOG("origin | destination | capacity | flow");
    // for (unsigned int i = 0; i < m_connections.size(); i++) {
    //     auto c = m_connections[i];
    //     LOG(std::to_string(c->getOrigin()->getId()) + " | "
    //     + std::to_string(c->getDestination()->getId()) + " | "
    //     + std::to_string(c->getCapacity()) + " | "
    //     + std::to_string(c->getFlow()));
    // }
    // LOG("\n");
    return getTail()->getExcessFlow();
}

std::shared_ptr<Node> Graph::getSource()
{
    return m_nodes[0];
}

std::shared_ptr<Node> Graph::getTail()
{
    return m_nodes.back();
}

std::shared_ptr<Node> Graph::getNode(int id)
{
    for(int i = 0; i < m_num_vertices; i++) {
        if(m_nodes[i]->getId() == id)
            return m_nodes[i];
    }
    return nullptr;
}

int Graph::getNodeIndex(std::shared_ptr<Node> node)
{
    int index = node->getId();

    if(isStorage(index)) {
        if(index < 0)
            index = -index + 1;
        
        index += index - (m_num_suppliers + 2);
    }

    return index;
}

bool Graph::isStorage(int node_id)
{
    return node_id > m_num_suppliers + 1 || node_id < 0;
}

void Graph::calculateIncreases()
{
    bool *visited = new bool[m_num_vertices];
    visited[0] = true;
    for(int i = 1; i < m_num_vertices; i++)
        visited[i] = false;
    calculateIncreasesRecursive(getTail(), visited);
    delete [] visited;
}

bool Graph::calculateIncreasesRecursive(std::shared_ptr<Node> node, bool *visited)
{
    int destination_index = getNodeIndex(node);
    visited[destination_index] = true;
    unsigned int connections_size = m_connections.size();
    for (unsigned int i = 0; i < connections_size; i++) {
        auto connection = m_connections[i];

        if(connection->getDestination() != node)
            continue;

        auto origin = connection->getOrigin();

        int origin_index = getNodeIndex(origin);
        if(visited[origin_index])
            continue;

        if(connection->getFlow() == connection->getCapacity()) {
            m_increases.push_back(connection);
        } else
            calculateIncreasesRecursive(origin, visited);
    }
    return false;
}

std::vector<std::shared_ptr<Connection>> Graph::getIncreases()
{
    return m_increases;
}
