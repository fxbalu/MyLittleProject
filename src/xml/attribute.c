/**
 * \file attribute.c
 * \brief XML attribute related functions
 *
 * Functions to use a XML_Tag structure.
 *
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 16 mars 2014
 */


#include "attribute.h"


/**
 * \brief Create a XML attribute.
 * Allocate memory for a XML attribute and set its members to NULL.
 *
 * \return Created XML attribute.
 */
XML_Attribute* createXMLAttribute(void)
{
   XML_Attribute* attr;

   attr = allocXMLAttribute(attr);
   initXMLAttribute(attr);

   return attr;
}


/**
 * \brief Destroy a XML attribute.
 * Free all memory allocated for a XML attribute, and accessible attributes
 * pointed by next member to prevent memory leaks.
 *
 * \param attr  Destroyed XML attribute.
 */
void destroyXMLAttribute(XML_Attribute* attr)
{
   if(attr == NULL) {
      logError("Trying to destroy a NULL attribute", __FILE__, __LINE__);
   }
   else {
      /* logMem(FREE, "string", __FILE__, __LINE__); */
      free(attr->name);
      /* logMem(FREE, "string", __FILE__, __LINE__); */
      free(attr->value);
      if(attr->next != NULL) {
         destroyXMLAttribute(attr->next);
      }
      /* logMem(FREE, "attribute", __FILE__, __LINE__); */
      free(attr);
   }
}


/**
 * \brief Allocate memory for a XM attribute.
 * Need more blah blah, like in allocXMLTag().
 *
 * \param attr  Tested XML attribute.
 * \return      Allocated XML attribute.
 */
XML_Attribute* allocXMLAttribute(XML_Attribute* attr)
{
   if(attr != NULL) {
      logError("Trying to allocate memory for a non NULL attribute",
               __FILE__, __LINE__);
   }
   else if((attr = malloc(sizeof(XML_Attribute))) == NULL) {
      logError("Can't allocate memory for an attribute", __FILE__, __LINE__);
   }
   else {
      /* logMem(ALLOC, "XML_Attribute", __FILE__, __LINE__) */
   }

   return attr;
}


/**
 * \brief Free an initialized XML attribute.
 * Free memory from a XML attribute. If attribute isn't in an initialized state,
 * it won't be freed to prevent memory leaks.
 *
 * \param attr Freed XML attribute.
 */
void freeXMLAttribute(XML_Attribute* attr)
{
   if(attr == NULL) {
      logError("Trying to free a NULL attribute", __FILE__, LINE__);
   }
   else if((attr->name != NULL) &&
           (attr->value != NULL) &&
           (attr->next != NULL)) {
      logError("Trying to free a non initialized attribute",
               __FILE__, __LINE__);
   }
   else {
      /* logMem(FREE, "XML_Attribute", __FILE__, __LINE__) */
      free(attr);
   }
}


/**
 * \brief Initialize an allocated attribute.
 * Set attribute's members to NULL. It can't check if members are used or not,
 * so memory leaks can happen here. You should use it immediately after
 * allocXMLAttribute().
 *
 * \param attr  Initialized attribute.
 */
void initXMLAttribute(XML_Attribute* attr)
{
   if(attr == NULL) {
      logError("Trying to initialize a NULL attr", __FILE__, __LINE__);
   }
   else {
      attr->name = NULL;
      attr->value = NULL;
      attr->next = NULL;
   }
}


/**
 * \brief Reset a XML attribute to its initial state.
 * Free memory allocated to attribute's members and initialize it. It does work
 * on already initialized attribute, but freeXMLAttribute() is better in this
 * case.
 *
 * Attributes are recursively freed to prevent memory leaks. Use
 * copyXMLAttribute() to pass an attribute to another structure, such as
 * XML_Node.
 *
 * Don't use this function on an allocated attribute, because free() has
 * undefined behavior on non allocated variable.
 *
 * \param attr  Reseted XML attribute.
 */
void resetXMLAttribute(XML_Attribute* attr)
{
   if(attr == NULL) {
      logError("Trying to reset a NULL attribute", __FILE__, __LINE__);
   }
   else {
      /* logMem(FREE, "string", __FILE__, __LINE__); */
      free(attr->name);
      /* logMem(FREE, "string", __FILE__, __LINE__); */
      free(attr->value);
      destroyXMLAttribute(tag->attr);
      initXMLAttribute(attr);
   }
}

void setXMLAttributeName(const char* name, XML_Attribute* a);
void setXMLAttributeValue(const char* value, XML_Attribute* a);

XML_Attribute* readXMLAttribute(FILE* file);

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   :::   Old functions                                                    :::
   ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/




/**
 * \brief Reset a XML attribute.
 * Set every attribute's members to NULL.
 *
 * \param attr  Reseted attribute.
 */
void resetXMLAttribute(XML_Attribute* attr)
{
   if(attr != NULL)
   {
      attr->name = NULL;
      attr->value = NULL;
      attr->next = NULL;
   }
}


/**
 * \brief Set an attribute's name.
 * Allocate memory for a attribute's name, and copy name's content in it.
 * If attribute already has a name, memory is reallocated instead.
 *
 * \param[in] name  Given name.
 * \param     attr  Modified attribute.
 */
void setXMLAttributeName(const char* name, XML_Attribute* a)
{
   /* NULL attribute */
   if(attr != NULL) {
      logError("Giving a name to a NULL attr", __FILE__, __LINE__);
   }
   /* attribute already has a name */
   else if(attr->name != NULL) {
      if((attr->name = realloc(attr->name, (strlen(name) + 1) * sizeof(char))) == NULL) {
         logError("Can't reallocate memory for attribute's name", __FILE__, __LINE__);
      }
      else {
         strcpy(tag->name, name);
      }
   }
   /* tag doesn't have a name */
   else {
      if((tag->name = malloc((strlen(name) + 1) * sizeof(char))) == NULL) {
         logError("can't allocate memory for tag's name", __FILE__, __LINE__);
      }
      else {
         /* logMem(ALLOC, "string", __FILE__, __LINE__) */
         strcpy(tag->name, name);
      }
   }
}


void setXMLAttributeValue(const char* value, XML_Attribute* a)
void printXMLAttribute(const XML_Attribute* a);

XML_Attribute* readXMLAttribute(FILE* file);


/*
   ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   :::    Old functions                                                   :::
   ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/


/**
 * \brief Allocate memory for an Attribute.
 *
 * \param a  Memoryless Attribute
 * \return   Memorized  Attribute
 *
 * \todo Remove need for parameter \p a
 * \todo use new logError() function instead of printf().
 */
Attribute* allocateAttribute(Attribute* a)
{
   if((a = malloc(sizeof(Attribute))) == NULL)
   {
      printf("\nerror in createAttribute(Attribute * a)");
   }

   return a;
}


/**
 * \brief Reset an Attribute.
 * Set an Attribute's members to NULL.
 *
 * \param a  Reseted Attribute
 */
void resetAttribute(Attribute* a)
{
   if(a != NULL)
   {
      a->name = NULL;
      a->value = NULL;
   }
}


/**
 * \brief Set a name for an Attribute.
 *
 * \param[in] name given name
 * \param     a    modified Attribute
 */
void setAttributeName(const char* name, Attribute* a)
{
   if(name != NULL && a != NULL)
   {
      if((a->name = malloc((strlen(name) + 1) * sizeof(char))) == NULL)
      {
         printf("error in setAttributeName()");
      }
      else
      {
         strcpy(a->name, name);
      }
   }
}


/**
 * \brief Set a value for an Attribute.
 *
 * \param[in] value given value
 * \param     a     modified Attribute
 */
void setAttributeValue(const char* value, Attribute* a)
{
   if(value != NULL && a != NULL)
   {
      if((a->value = malloc((strlen(value) + 1) * sizeof(char))) == NULL)
      {
         printf("error in setAttributeValue()");
      }
      else
      {
         strcpy(a->value, value);
      }
   }
}


/**
 * \brief Insert an Attribute in a Node.
 * Insert an Attribute in a Node before the first Attribute already attached to
 * said Node.
 *
 * \param a  Added Attribute.
 * \param n  Modified Node.
 */
void insertFirstAttribute(Attribute* a, Node* n)
{
   if((a != NULL) && (n != NULL))
   {
      a->next = n->attr;
      n->attr = a;
   }
}

/**
 * \brief Insert an Attribute in a Node.
 * Insert an Attribute in a Node after the last Attribute already attached to
 * said Node.
 *
 * \param a  Added Attribute.
 * \param n  Modified Node.
 */
void insertLastAttribute(Attribute* a, Node* n)
{
   Attribute* temp;

   if(n != NULL)
   {
      /* No Attribute attached to Node */
      if(n->attr == NULL)
      {
         n->attr = a;
      }
      /* One Attribute or more */
      else
      {
         temp = n->attr;
         while(temp->next != NULL)
         {
            temp = temp->next;
         }
         temp->next = a;
      }
   }
}


/**
 * \brief Delete the first Attribute of a Node.
 * Deleted Node is not freed from memory.
 *
 * \param n  Modified Node
 * \return   Deleted Attribute
 */
Attribute* deleteFirstAttribute(Node* n)
{
   Attribute* deleted;

   deleted = NULL;
   if(n != NULL)
   {
      deleted = n->attr;
      /* One or more Attribute attached to Node */
      if(deleted != NULL)
      {
         n->attr = deleted->next;
         deleted->next = NULL;
      }

   }

   return deleted;
}


/**
 * \brief Delete the last Attribute of a Node
 *
 * \param n  Modified Node
 * \return   Deleted Attribute
 */
Attribute* deleteLastAttribute(Node* n)
{
   Attribute* temp, * deleted;

   deleted = NULL;
   if(n != NULL)
   {
      /* At least one Attribute attached to Node */
      if(n->attr != NULL)
      {
         temp = n->attr;
         /* Only one Attribute */
         if(temp->next == NULL)
         {
            deleted = temp;
            n->attr = NULL;
         }
         /* Two or more Attribute */
         else
         {
            while(temp->next->next != NULL)
            {
               temp = temp->next;
            }
            deleted = temp->next;
            temp->next = NULL;
         }
      }
   }

   return deleted;
}


/**
 * \brief Tell if a Node has Attribute or not.
 *
 * \param n  Checked Node.
 * \return   \c true if Node n has at least one Attribute, \c false if not.
 */
Boolean hasAttribute(Node* n)
{
   return(n->attr != NULL);
}





/**
 * \brief Destroy an Attribute and the ones after it.
 * Destroy Attribute first, then Attribute pointed by first->next, then
 * Attribute pointed by first->next->next, etc.
 * \see destroyAttribute
 *
 * \param first  First destroyed Attribute
 */
void destroyNextAttributes(Attribute* first)
{
   Attribute* temp;

   temp = first;
   while(temp != NULL) {
      temp = destroyAttribute(temp);
   }
}


/**
 * \brief Destroy every Attributes of a Node
 * Free memory allocated to members (name and value) and Attributes.
 *
 * \param n  Node where Attributes are destroyed.
 */
void destroyEveryAttributes(Node* n)
{
   Attribute* temp;

   if(n != NULL)
   {
      while(hasAttribute(n))
      {
         temp = deleteFirstAttribute(n);
         if(temp->name != NULL)
            free(temp->name);
         if(temp->value != NULL)
            free(temp->value);
         free(temp);
      }
   }

}
