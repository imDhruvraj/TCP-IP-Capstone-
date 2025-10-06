#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

graph_t *create_new_graph(char *topology_name) {
    graph_t *graph = (graph_t *)malloc(sizeof(graph_t));
    strncpy(graph->topology_name, topology_name, sizeof(graph->topology_name));
    graph->node_count = 0;
    return graph;
}

node_t *create_graph_node(graph_t *graph, char *node_name) {
    node_t *node = (node_t *)malloc(sizeof(node_t));
    strncpy(node->node_name, node_name, NODE_NAME_SIZE);
    for(int i=0; i<MAX_INTF_PER_NODE; i++)
        node->intf[i] = NULL;
    graph->node_list[graph->node_count++] = node;
    return node;
}

void insert_link_between_two_nodes(node_t *node1, node_t *node2, char *from_if_name, char *to_if_name, unsigned int cost) {
    link_t *link = (link_t *)malloc(sizeof(link_t));

    // Setup intf1
    strncpy(link->intf1.if_name, from_if_name, IF_NAME_SIZE);
    link->intf1.owner = node1;
    link->intf1.link = link;

    // Setup intf2
    strncpy(link->intf2.if_name, to_if_name, IF_NAME_SIZE);
    link->intf2.owner = node2;
    link->intf2.link = link;

    link->cost = cost;

    // Attach interfaces to nodes
    for (int i = 0; i < MAX_INTF_PER_NODE; i++) {
        if (node1->intf[i] == NULL) {
            node1->intf[i] = &link->intf1;
            break;
        }
    }
    for (int i = 0; i < MAX_INTF_PER_NODE; i++) {
        if (node2->intf[i] == NULL) {
            node2->intf[i] = &link->intf2;
            break;
        }
    }
}


void dump_graph(graph_t *graph) {
    printf("\nTopology Name: %s\n", graph->topology_name);
    printf("--------------------------------------\n");

    for (int i = 0; i < graph->node_count; i++) {
        node_t *node = graph->node_list[i];
        printf("Node %s:\n", node->node_name);

        for (int j = 0; j < MAX_INTF_PER_NODE; j++) {
            interface_t *intf = node->intf[j];
            if (!intf) continue;

            link_t *link = intf->link;
            interface_t *nbr_intf;

            // figure out the opposite end of the link
            if (&link->intf1 == intf)
                nbr_intf = &link->intf2;
            else
                nbr_intf = &link->intf1;

            printf("  Interface %-8s --> Node %-8s (Cost: %u)\n",
                   intf->if_name,
                   nbr_intf->owner->node_name,
                   link->cost);
        }
        printf("\n");
    }
}

