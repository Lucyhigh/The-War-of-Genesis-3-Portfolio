#pragma once
#include <functional>
#include <set>

namespace AStar
{
    struct Vec2i
    {
        int x, y;

        bool operator == (const Vec2i& coordinates);
    };

    using uint = unsigned int;
    using HeuristicFunction = function<uint(Vec2i, Vec2i)>;
    using CoordinateList = vector<Vec2i>;

    struct Node
    {
        uint G, H;
        Vec2i coordinates;
        Node *parent;

        Node(Vec2i coord, Node *parent = nullptr);
        uint getScore();
    };

    using NodeSet = std::vector<Node*>;

    class Generator
    {
        bool detectCollision(Vec2i coordinates);
        Node* findNodeOnList(NodeSet& nodes, Vec2i coordinates);
        void releaseNodes(NodeSet& nodes);

    public:
        Generator();
        void setWorldSize(Vec2i worldSize);
        void setDiagonalMovement(bool enable);
        void setHeuristic(HeuristicFunction heuristic);
        CoordinateList findPath(Vec2i source, Vec2i target);
        void addCollision(Vec2i coordinates);
        void removeCollision(Vec2i coordinates);
        void clearCollisions();

    private:
        HeuristicFunction heuristic;
        CoordinateList direction, walls;
        Vec2i worldSize;
        uint directions;
    };

    class Heuristic
    {
        static Vec2i getDelta(Vec2i source, Vec2i target);

    public:
        static uint manhattan(Vec2i source, Vec2i target);
        static uint euclidean(Vec2i source, Vec2i target);
        static uint octagonal(Vec2i source, Vec2i target);
    };
}