#include "Graph.hpp"

Graph::Graph(int num_vertices) : m_num_vertices(num_vertices) {
    auto source = std::make_shared<Node>(0);
    addNode(source);
    m_num_vertices++;
}

void Graph::addNode(std::shared_ptr<Node> node)
{
    m_nodes.push_back(node);
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
            connection->addFlow(connection->getCapacity());

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

    return m_nodes.back()->getExcessFlow();
}

std::shared_ptr<Node> Graph::getSource()
{
    return m_nodes[0];
}

std::shared_ptr<Node> Graph::getNode(int id)
{
    for(int i = id; i < m_num_vertices; i++) {
        if(m_nodes[i]->getId() == id)
        return m_nodes[i];
    }
    return nullptr;
}