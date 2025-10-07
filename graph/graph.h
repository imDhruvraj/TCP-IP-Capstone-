#ifndef GRAPH_H
#define GRAPH_H

#define NODE_NAME_SIZE 16
#define IF_NAME_SIZE   16
#define MAX_INTF_PER_NODE 10

typedef struct node_ node_t;
typedef struct link_ link_t;

typedef struct interface_ {
    char if_name[IF_NAME_SIZE];
    struct node_ *owner;                   // owning node
    link_t *link;                          // link it belongs to
} interface_t;

struct link_ {
    interface_t intf1;
    interface_t intf2;
    unsigned int cost;
};

struct node_ {
    char node_name[NODE_NAME_SIZE];
    interface_t *intf[MAX_INTF_PER_NODE];  // list of interfaces
};

typedef struct graph_ {
    char topology_name[32];
    node_t *node_list[100];                // for simplicity, fixed size
    int node_count;
} graph_t;

graph_t *create_new_graph(char *topology_name);
node_t *create_graph_node(graph_t *graph, char *node_name);
void insert_link_between_two_nodes(node_t *node1, node_t *node2, char *from_if_name, char *to_if_name, unsigned int cost);
void dump_graph(graph_t *graph);

#endif
