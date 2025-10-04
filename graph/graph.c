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

void insert_link_between_two_nodes(node_t *node1, node_t *node2,
                                   char *from_if_name, char *to_if_name,
                                   unsigned int cost) {
    link_t *link = (link_t *)malloc(sizeof(link_t));

    strncpy(link->intf1.if_name, from_if_name, IF_NAME_SIZE);
    strncpy(link->intf2.if_name, to_if_name, IF_NAME_SIZE);

    link->intf1.owner = node1;
    link->intf2.owner = node2;

    link->intf1.link = link;
    link->intf2.link = link;

    link->cost = cost;
}

void dump_graph(graph_t *graph) {
    printf("Graph: %s\n", graph->topology_name);
    for(int i=0; i<graph->node_count; i++) {
        node_t *node = graph->node_list[i];
        printf(" Node %s\n", node->node_name);
    }
}
