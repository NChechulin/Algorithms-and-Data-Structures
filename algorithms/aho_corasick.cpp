
#ifndef AHOCORASICK_H
#define AHOCORASICK_H

#include "tries.h"
#include <map>
#include <queue>
#include <iostream>
#include <valarray>

class AhoCorasickTrie : public Trie
{
public:

    AhoCorasickTrie(const std::vector<std::string> &patterns)
    {
        std::vector<std::string> realPatterns = patterns;

        for (auto &pattern: patterns)
        {
            int qmAt = pattern.rfind("?");
            if (qmAt >= 0)
            {
                for (int to = 0; to !=qmAt; to++){
                    std::string newPattern = pattern.substr(0, to) + '?';
                    realPatterns.push_back(newPattern);
            }}
        }


        for (auto &pattern: patterns)
        {
            Node *endNode = this->insert(pattern);
            this->patterns[endNode] = pattern;
        }

        buildSuffixLinks();
        printSuffixLinks();
    }

    void find(const std::string &text)
    {
        Node *currentNode = _root;
        for (int i = 0; i < text.size(); i++)
        {
            char a = text[i];

            while ((!aOfX(currentNode, a)) and currentNode != _root)
                currentNode = suffixLink[currentNode];

            if ((!aOfX(currentNode, a)) and currentNode == _root)
                continue;

            currentNode = aOfX(currentNode, a);
            if (currentNode->endOfWord)
                // We have found a pattern in position ??? of the text! Print position and pattern
            {
                int foundAt = i + 1 - this->patterns[currentNode].size();
                int pattLen = this->patterns[currentNode].size();

                std::cout << "match object " << text.substr(foundAt, pattLen)
                          << "\vfound at position " << foundAt << '\n';
            }
            Node *v = outputLink[currentNode] ? outputLink[currentNode] : nullptr;
            while (v)
                // We have a found a pattern in position ??? of the text! Print position and pattern
            {
                int foundAt = i + 1 - this->patterns[v].size();
                int pattLen = this->patterns[v].size();

                std::cout << "match object " << text.substr(foundAt, pattLen)
                          << " found at position " << foundAt << '\n';
                v = outputLink[v] ? outputLink[v] : nullptr;
            }
        }

    }

    void printSuffixLinks()
    {

        std::queue<Node *> q;
        q.push(_root);

        while (!q.empty())
        {
            Node *current = q.front();
            q.pop();

            for (Node *child: current->children)
                if (child)
                    q.push(child);

            if (current == _root)
                continue;

            Node *suff_link = suffixLink[current];
            if (suff_link)
            {
                if (suff_link == _root)
                    std::cout << current->c << " -> "
                              << "root" << '\n';
                else
                    std::cout << current->c << " -> " << suff_link->c << '\n';

            } else
            {
                std::cout << current->c << " -> "
                          << "nullptr" << '\n';
            }
        }
    }

private:

    void buildOutputLink(Node *u)
    {
        Node *v = suffixLink[u];
        if (v and v->endOfWord)
            outputLink[u] = v;
        else if (outputLink[v])
            outputLink[u] = outputLink[v];
    }

    Node *aOfX(Node *x, char a)
    {

        if (!x)
            return nullptr;
        for (Node *child: x->children)
            if (child)
                if ((child->c == a) or (child->c == '?'))
//                if (child->c == a)
                    return child;
        return nullptr;
    }

    void buildSuffixLinks()
    {
        // Your code here! ;-) (Follow slide 67)
        std::queue<Node *> queue;

        auto root = this->_root;
        suffixLink[root] = nullptr;

        /*** go through root's children ***/
        for (auto crrChild: root->children)
            if (crrChild)
            {
                suffixLink[crrChild] = root;
                queue.push(crrChild);
            }

        /*** go through the queue. the queue doesn't contain nullptr ***/
        while (!queue.empty())
        {
            Node *w = queue.front();
//            std::cout << w->c;
            for (Node *a: w->children)
                if (a)
                {
                    /*** Create suffix link for node wa ***/
                    Node *x = suffixLink[w];
                    while ((x) and (!aOfX(x, a->c)))
                        x = suffixLink[x];

                    if (!x)
                        suffixLink[a] = root;
                    else
                        suffixLink[a] = aOfX(x, a->c);

                    buildOutputLink(a);

                    queue.push(a);
                }
            queue.pop();
        }



        // P.S: print also suffix links in the console when you assign then! (Like in the example of slide 89)
    }

    std::map<Node *, std::string> patterns;
    std::vector<std::string> realPatterns;

    std::map<Node *, Node *> suffixLink;

    std::map<Node *, Node *> outputLink;
};

#endif