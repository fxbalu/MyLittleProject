/**
 * \file list.c
 * \brief List related functions
 *
 * Functions used to work on Node as a list.
 *
 * \author François-Xavier Balu <fx.balu@gmail.com>
 * \date 12 mars 2014
 */


#include "node.h"


/**
 * \brief Tell if a Node has children.
 * \param[in] n Tested Node.
 * \return      \c true if Node \p n has children Nodes, \c false if not.
 */
boolean hasNodeChildren(Node * n) {
   if(n == NULL) {
      return false;
      }
   else {
      if(n->first == NULL) {
         return false;
         }
      else {
         return true;
         }
      }
   }


/**
 * \brief Tell if Node has a parent.
 * \param n  Tested Node.
 * \return   \c true if \p n has a parent Node, \c false if not.
 */
boolean hasNodeParent(Node * n) {
   if(n == NULL) {
      return false;
      }
   else {
      if(n->parent == NULL) {
         return false;
         }
      else {
         return true;
         }
      }
   }


/**
 * \brief Print a Node's data in the terminal.
 *
 * \param[in] n     Read Node.
 * \param[in] mode  Quantity of informations displayed.
 *                  1 = few informations (name and value)
 *                  2 = more informations (name, value and names of parent,
 *                      siblings and children)
 *                  3 = lot of informations (WIP)
 * \todo Implement mode 2 and 3.
 */
void printNode(const Node * n, const int mode) {
   if(n == NULL) {
      printf("Node doesn't exist (NULL pointer).\n");
      }
   else {
      /* Name */
      if(n->name == NULL)  printf("Name = NULL\n");
      else                 printf("Name = \"%s\"\n", n->name);
      /* Value */
      if(n->value == NULL) printf("Value = NULL\n");
      else                 printf("Value = \"%s\"\n", n->value);
      }
   }


/**
 * \brief Insert a Node in first position.
 * \param child   Added Node.
 * \param parent  Parent Node that will contain \p child.
 */
void insertFirst(Node * child, Node * parent) {
   if((child != NULL) && (parent != NULL)) {
      if(hasNodeChildren(parent)) {
         /* Link between child Node and NULL */
         child->previous == NULL;
         /* Links between child Node and first Node */
         child->next == parent->first;
         parent->first->previous == child;
         /* Links between child Node and parent Node */
         parent->first = child;
         child->parent = parent;
         }
      else {
         /* Links between child Node and NULL */
         child->previous == NULL;
         child->next == NULL;
         /* Links between child Node and parent Node */
         parent->first = child;
         parent->current = child;
         parent->last = child;
         child->parent = parent;
         }
      parent->cc++;
      }
   }


/**
 * \brief Insert a node in last position.
 * \param child   Added Node.
 * \param parent  Parent Node that will contain \p child.
 */
void insertLast(Node * child, Node * parent) {
   if((child != NULL) && (parent != NULL)) {
      if(hasNodeChildren(parent)) {
         /* Link between child Node and NULL */
         child->next == NULL;
         /* Links between child Node and last Node */
         child->previous == parent->last;
         parent->last->next == child;
         /* Links between child Node and parent Node */
         parent->last = child;
         child->parent = parent;
         }
      else {
         /* Links between child Node and NULL */
         child->previous == NULL;
         child->next == NULL;
         /* Links between child Node and parent Node */
         parent->first = child;
         parent->current = child;
         parent->last = child;
         child->parent = parent;
         }
      parent->cc++;
      }
   }


/**
 * \brief Delete the first child Node of a Node's children.
 * The deleted Node is not freed from ram.
 *
 * \param parent  Modified parent Node.
 * \return        Deleted child Node.
 */
Node * deleteFirstNodeList(Node * parent) {
   Node * temp;

   temp = NULL;
   if(parent != NULL) {
      if(hasNodeChildren(parent)) {
         temp = parent->first;

         /* One node */
         if(temp == parent->last)
            parent->first = parent->current = parent->last = NULL;

         /* Two nodes or more */
         else {
            /* change next node */
            temp->next->previous = NULL;

            /* change parent */
            if(temp == parent->current)
               parent->current = temp->next;
            parent->first = temp->next;

            /* change deleted node */
            temp->next = NULL;
            }
         parent->cc--;
         }
      }

   return temp;
   }


/**
 * \brief Delete the last child Node of a Node's children.
 * The deleted Node is not freed from ram.
 *
 * \param parent  Modified parent Node.
 * \return        Deleted child Node.
 */
Node * deleteLastNodeList(Node * parent) {
   Node * temp;

   temp = NULL;
   if(parent != NULL) {
      if(hasNodeChildren(parent)) {
         temp = parent->last;

         /* One node */
         if(temp == parent->first)
            parent->first = parent->current = parent->last = NULL;

         /* Two nodes or more */
         else {
            /* change previous node */
            temp->previous->next = NULL;

            /* change parent */
            if(temp == parent->current)
               parent->current = temp->previous;
            parent->last = temp->previous;

            /* change deleted node */
            temp->previous = NULL;
            }
         parent->cc--;
         }
      }

   return temp;
   }


/**
 * \brief Use a function on each child Node of a parent Node.
 * Use given function on every child Node of a parent Node, from first to last.
 *
 * \param[in] parent  Parent Node
 * \param     fn      function used on child Nodes. Take a Node as parameter.
 */
void forEachNodeChild(Node * parent, void (*fn)(Node *)) {
   Node * temp;

   if(parent != NULL) {
      if(hasNodeChildren(parent)) {
         temp = parent->first;
         while(temp != parent->last) {
            temp = temp->next;
            (*fn)(temp->previous);
            }
         (*fn)(temp);
         }
      }
   }
