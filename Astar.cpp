#include "Stdafx.h"
#include "AStar.h"
#include <algorithm>
#include <math.h>

using namespace std::placeholders;

bool AStar::Vec2i::operator == (const Vec2i& coordinates_)
{
    return (x == coordinates_.x && y == coordinates_.y);
}

AStar::Vec2i operator + (const AStar::Vec2i& left_, const AStar::Vec2i& right_)
{
    return{ left_.x + right_.x, left_.y + right_.y };
}

AStar::Node::Node(Vec2i coordinates_, Node *parent_)
{
    parent = parent_;
    coordinates = coordinates_;
    G = H = 0;
}

AStar::uint AStar::Node::getScore()
{
    return G + H;
}

AStar::Generator::Generator()
{
    setDiagonalMovement(false);
    setHeuristic(&Heuristic::manhattan);
    direction = {
        { 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 },
        { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }
    };
}

void AStar::Generator::setWorldSize(Vec2i worldSize)
{
    worldSize = worldSize;
}

void AStar::Generator::setDiagonalMovement(bool enable)
{
    directions = (enable ? 8 : 4);
}

void AStar::Generator::setHeuristic(HeuristicFunction heuristic)
{
    heuristic = std::bind(heuristic, _1, _2);
}

void AStar::Generator::addCollision(Vec2i coordinates)
{
    walls.push_back(coordinates);
}

void AStar::Generator::removeCollision(Vec2i coordinates)
{
    auto it = std::find(walls.begin(), walls.end(), coordinates);
    if (it != walls.end()) {
        walls.erase(it);
    }
}

void AStar::Generator::clearCollisions()
{
    walls.clear();
}

AStar::CoordinateList AStar::Generator::findPath(Vec2i source, Vec2i target)
{
    Node *current = nullptr;
    NodeSet openSet, closedSet;
    openSet.reserve(100);
    closedSet.reserve(100);
    openSet.push_back(new Node(source));

    while (!openSet.empty()) {
        auto current_it = openSet.begin();
        current = *current_it;

        for (auto it = openSet.begin(); it != openSet.end(); it++) {
            auto node = *it;
            if (node->getScore() <= current->getScore()) {
                current = node;
                current_it = it;
            }
        }

        if (current->coordinates == target) {
            break;
        }

        closedSet.push_back(current);
        openSet.erase(current_it);

        for (uint i = 0; i < directions; ++i) {
            Vec2i newCoordinates(current->coordinates + direction[i]);
            if (detectCollision(newCoordinates) ||
                findNodeOnList(closedSet, newCoordinates)) {
                continue;
            }

            uint totalCost = current->G + ((i < 4) ? 10 : 14);

            Node *successor = findNodeOnList(openSet, newCoordinates);
            if (successor == nullptr) {
                successor = new Node(newCoordinates, current);
                successor->G = totalCost;
                successor->H = heuristic(successor->coordinates, target);
                openSet.push_back(successor);
            }
            else if (totalCost < successor->G) {
                successor->parent = current;
                successor->G = totalCost;
            }
        }
    }

    CoordinateList path;
    while (current != nullptr) {
        path.push_back(current->coordinates);
        current = current->parent;
    }
    releaseNodes(openSet);
    releaseNodes(closedSet);

    return path;
}

AStar::Node* AStar::Generator::findNodeOnList(NodeSet& nodes, Vec2i coordinates)
{
    for (auto node : nodes) {
        if (node->coordinates == coordinates) {
            return node;
        }
    }
    return nullptr;
}

void AStar::Generator::releaseNodes(NodeSet& nodes)
{
    for (auto it = nodes.begin(); it != nodes.end();) {
        delete *it;
        it = nodes.erase(it);
    }
}

bool AStar::Generator::detectCollision(Vec2i coordinates)
{
    if (coordinates.x < 0 || coordinates.x >= worldSize.x ||
        coordinates.y < 0 || coordinates.y >= worldSize.y ||
        std::find(walls.begin(), walls.end(), coordinates) != walls.end()) {
        return true;
    }
    return false;
}

AStar::Vec2i AStar::Heuristic::getDelta(Vec2i source, Vec2i target)
{
    return{ abs(source.x - target.x),  abs(source.y - target.y) };
}

AStar::uint AStar::Heuristic::manhattan(Vec2i source, Vec2i target)
{
    auto delta = std::move(getDelta(source, target));
    return static_cast<uint>(10 * (delta.x + delta.y));
}

AStar::uint AStar::Heuristic::euclidean(Vec2i source, Vec2i target)
{
    auto delta = std::move(getDelta(source, target));
    return static_cast<uint>(10 * sqrt(pow(delta.x, 2) + pow(delta.y, 2)));
}

AStar::uint AStar::Heuristic::octagonal(Vec2i source, Vec2i target)
{
    auto delta = std::move(getDelta(source, target));
	int minValue = delta.x < delta.y ? delta.x : delta.y;
    return 10 * (delta.x + delta.y) + (-6) * minValue;
}
