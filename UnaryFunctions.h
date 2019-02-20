//
// Created by avbol on 12.12.2018.
//

#ifndef DIFFERENCIATOR_UNARYFUNCTIONS_H
#define DIFFERENCIATOR_UNARYFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

DIFF_DEF(sin,
        {
            char cosinus[] = "cos";
            char multiply[] = "*";

            out_node = new Node(multiply, FUNC,
                                nullptr, nullptr, nullptr);

            out_node->left = new Node(cosinus, FUNC,
                                      nullptr, nullptr, nullptr);
            out_node->left->right = new Node(node->right);

            out_node->right = DiffNode(node->right);
        })

DIFF_DEF(cos,
        {
            char sinus[] = "sin";
            char multiply[] = "*";
            char minus_one[] = "-1";

            out_node = new Node(multiply, FUNC,
                                nullptr, nullptr, nullptr);
            out_node->left = new Node(multiply, FUNC,
                                      nullptr, nullptr, nullptr);

            out_node->left->left = new Node(minus_one, NUM,
                                      nullptr, nullptr, nullptr);


            out_node->left->right = new Node(sinus, FUNC,
                                      nullptr, nullptr, nullptr);
            out_node->left->right->right = new Node(node->right);

            out_node->right = DiffNode(node->right);
        })

DIFF_DEF(tg,
        {
            char divid[] = "/";
            char power[] = "^";
            char multiply[] = "*";
            char cosinus[] = "cos";
            char one[] = "1";
            char two[] = "2";

            out_node = new Node(multiply, FUNC,
                                nullptr, nullptr, nullptr);
            out_node->left = new Node(divid, FUNC,
                                      nullptr, nullptr, nullptr);

            out_node->left->left = new Node(
                     one, NUM, nullptr,
                     nullptr, nullptr);

            out_node->left->right = new Node(
                    power, FUNC, nullptr,
                    nullptr, nullptr);

            out_node->left->right->left = new Node(
                    cosinus, FUNC, nullptr,
                    nullptr, nullptr);
            out_node->left->right->left->right = new Node(
                    node->right);

            out_node->left->right->right = new Node(
                    two, NUM, nullptr,
                    nullptr, nullptr);

            out_node->right = DiffNode(node->right);
        })

DIFF_DEF(ctg,
        {
            char divid[] = "/";
            char power[] = "^";
            char sinus[] = "sin";
            char minus_one[] = "-1";
            char two[] = "2";
            char multiply[] = "*";

            out_node = new Node(multiply, FUNC,
                                nullptr, nullptr, nullptr);
            out_node->left = new Node(divid, FUNC,
                                      nullptr, nullptr, nullptr);
            out_node->left->left = new Node(
                     minus_one, NUM, nullptr,
                     nullptr, nullptr);

            out_node->left->right = new Node(
                    power, FUNC, nullptr,
                    nullptr, nullptr);

            out_node->left->right->left = new Node(
                    sinus, FUNC, nullptr,
                    nullptr, nullptr);
            out_node->left->right->left = new Node(
                    node->right);

            out_node->left->right->right = new Node(
                    two, NUM, nullptr,
                    nullptr, nullptr);

            out_node->right = DiffNode(node->right);
        })

DIFF_DEF(ln,
        {
            char divid[] = "/";
            char multiply[] = "*";
            char one[] = "1";

            out_node = new Node(multiply, FUNC,
                                nullptr, nullptr, nullptr);
            out_node->left = new Node(divid, FUNC,
                                      nullptr, nullptr, nullptr);
            out_node->left->left = new Node(
                    one, NUM, nullptr,
                    nullptr, nullptr);
            out_node->left->right = new Node(node->right);

            out_node->right = DiffNode(node->right);

        })
#endif //DIFFERENCIATOR_UNARYFUNCTIONS_H
