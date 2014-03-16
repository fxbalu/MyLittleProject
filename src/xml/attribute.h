/**
 * \file attribute.h
 * \brief XML attribute related definitions
 *
 * Definition of a XML_Attribute structure and functions to use it.
 *
 * \author François-Xavier Balu \<fx.balu@gmail.com\>
 * \date 16 mars 2014
 */


#ifndef ATTRIBUTE_H_INCLUDED
#define ATTRIBUTE_H_INCLUDED


/**
 * \struct XML_Attribute
 * \brief A XML node's attribute.
 */
typedef struct XML_Attribute
{
   char* name;    /**< attribute's name. */
   char* value;   /**< attribute's value. */
   struct XML_Attribute* next;   /**< Next attribute. */

} XML_Attribute;


XML_Attribute* createXMLAttribute(void);
void destroyXMLAttribute(XML_Attribute* attr);

XML_Attribute* allocXMLAttribute(XML_Attribute* attr);
void freeXMLAttribute(XML_Attribute* attr);

void initXMLAttribute(XML_Attribute* attr);
void resetXMLAttribute(XML_Attribute* attr);

void setXMLAttributeName(const char* name, XML_Attribute* a);
void setXMLAttributeValue(const char* value, XML_Attribute* a);

XML_Attribute* readXMLAttribute(FILE* file);

/* ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   :::   Example                                                          :::
   ::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
*/

XML_Tag* createXMLTag(void);
void destroyXMLTag(XML_Tag* tag);

XML_Tag* allocXMLTag(XML_Tag* tag);
void freeXMLTag(XML_Tag* tag);

void initXMLTag(XML_Tag* tag);
void resetXMLTag(XML_Tag* tag);

void setXMLTagName(const char* name, XML_Tag* tag);
void addAttributeToXMLTag(Attribute* attr, XML_Tag* tag);
XML_Tag* deleteAttributeFromXMLTag(XML_Tag* tag);

XML_Tag* readXMLTag(FILE* file);

#endif // ATTRIBUTE_H_INCLUDED
