/*
 * Code for a k-d tree implementaion for a 2-dimensional space.
 */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <functional>
#include <utility>

struct point{
    int x, y;
};

struct Node{
    point *p;
    Node *left;
    Node *right;

    Node(point &p_){
        p = new point({p_.x, p_.y});
        left == nullptr;
        right == nullptr;
    }
};

class KDTree{
private:
    Node *root;

    Node * insert(point &p, Node *node){
        if(node == nullptr){
            node = new Node(p);
            return node;
        }

        if(node->p->x > p.x){
            node->left = insert(p, node->left);
        }
        else{
            node->right = insert(p, node->right);
        }
        return node;
    }

    void traverse(Node *node){
        if (node == nullptr)
            return;
        std::cout << node->p->x << ' ' << node->p->y << '\n';
        traverse(node->left);
        traverse(node->right);
    }

    int getMedian(std::vector<point> &points, int l, int r, bool x){
        if(l == r){
            return l;
        }

        if(x){
            return (l + r) >> 1;
        }

        std::priority_queue<std::pair<int, int>> p1;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>,
                            std::greater<std::pair<int, int>>> p2;
        int mid = points[l].y;
        p1.push(std::make_pair(mid, l));
        for(int i = l + 1; i <= r; ++i){
            int temp = points[i].y;
            if(p1.size() > p2.size()){
                if(temp < mid){
                    p2.push(p1.top());
                    p1.pop();
                    p1.push(std::make_pair(temp, i));
                }
                else{
                    p2.push(std::make_pair(temp, i));
                }
                mid = p1.top().first;
            }
            else if(p1.size() == p2.size()){
                if(temp < mid){
                    p1.push(std::make_pair(temp, i));
                    mid = p1.top().first;
                }
                else{
                    p2.push(std::make_pair(temp, i));
                    mid = p2.top().first;
                }
            }
            else{
                if(temp < mid){
                    p1.push(std::make_pair(temp, i));
                }
                else{
                    p1.push(p2.top());
                    p2.pop();
                    p2.push(std::make_pair(temp, i));
                }
                mid = p2.top().first;
            }
        }
        if(p2.size() > p1.size()){
            return p2.top().second;
        }
        else{
            return p1.top().second;
        }
    }

    void insert(std::vector<point> &points, int l, int r, bool x){
        // std::cout << l << ' ' << r << '\n';
        if(l > r)
            return;
        int median = getMedian(points, l, r, x);
        insert(points[median]);
        insert(points, l, median - 1, x ^ 1);
        insert(points, median + 1, r,  x ^ 1);
    }

public:
    KDTree(){
        root = nullptr;
    }

    void insert(point p){
        if(root == nullptr){
            root = new Node(p);
            return;
        }
        insert(p, root);
    }

    void insert(std::vector<point> &points){
        // function to insert medians.
        // proper implementation would require use of a data 
        // structure like segment tree

        // sort the points with respect to x
        std::sort(points.begin(), points.end(),
                  [](const point &l, const point &r) -> bool {
                      if (l.x == r.x)
                          return l.y < r.y;
                      else
                          return l.x < r.x;
                  });
        
        insert(points, 0, points.size() - 1, true);

    }

    void traverse(){
        // preorder traversal
        traverse(root);
    }
};

int main(){
    std::vector<point> points = {{20, 50},
                                {5, 25},
                                {15, 55},
                                {30, 40},
                                {35, 20}};

    KDTree tree;
    tree.insert(points);
    // tree.insert(point({1, 2}));
    // tree.insert(point({-1, 2}));
    // tree.insert(point({3, 2}));
    // tree.insert(point({2, 2}));
    tree.traverse();
    return 0;
}
