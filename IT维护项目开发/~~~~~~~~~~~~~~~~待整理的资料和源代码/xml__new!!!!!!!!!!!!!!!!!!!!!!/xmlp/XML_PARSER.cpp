#include <stdafx.h>
#include <atlbase.h>
#include "XML_PARSER.h"

XML_PARSER::XML_PARSER()
{	// Constructor

	// Init our members
	//
	this->AttribNames.RemoveAll();
	this->AttribValues.RemoveAll();
	this->Tag.Empty();
	this->Name.Empty();
	this->ChainTag.Empty();
	this->TextField.Empty();

	// Init MSXML members
	//
	CurrentElementNode = NULL;
	m_plDomDocument = NULL;
	m_pDocRoot = NULL;

	attrib_index = -1;

	// -- Errors Init --
	//
	ok.Empty();
	ok = "Success";
	lasterror = ok;
}

XML_PARSER::~XML_PARSER()
{ 	// Free ressource
	//
	this->Reset_XML_Document();
}

CString & XML_PARSER::Get_LastError()
{ return lasterror; }

bool XML_PARSER::Init_MSXML()
{	lasterror = ok;

	// -- Init OLE Object Comunication for MSXML (only once time)--
	//
	static bool ole_initialized = false;
	if(!ole_initialized)
	{	::AfxOleInit();
		ole_initialized = true;
	}

	// -- Instantiate an XML document --
	//
	HRESULT hr = m_plDomDocument.CreateInstance(CLSID_DOMDocument);
	if (FAILED(hr))
	{ 	_com_error er(hr);
		lasterror = er.ErrorMessage();
		return false;
	}

	return true;
}

bool XML_PARSER::Load_XML_Document(LPCTSTR strFileName)
{	lasterror = ok;

	// Reset Document
	//
	this->Reset_XML_Document();

	// Convert xml file name string to something COM can handle (BSTR)
	//
	CString sFileName = strFileName;
	_bstr_t bstrFileName;
	bstrFileName = sFileName.AllocSysString();

	// Call the IXMLDOMDocumentPtr's load function to load the XML document
	//
	variant_t vResult;
	vResult = m_plDomDocument->load(bstrFileName);
	if (((bool)vResult) == TRUE) // success!
	{
		// Now that the document is loaded, we need to initialize the root pointer
		//
		m_pDocRoot = m_plDomDocument->documentElement;

		// Now we can Parse this document !!
		// 
		Parse_Objects(m_pDocRoot);

		this->Go_to_Root();

		return true;
	}
	else
	{	// XML document is not loaded, return error
		//
		lasterror = "XML Document FAILED to load";
		return false;
	}
}

void XML_PARSER::Parse_XML_Document()
{ /* Nothing to do , this method will be redefined in derived class */ }

void XML_PARSER::Parse_Objects(IXMLDOMNodePtr pObject)
{
	// Child node
	//
	IXMLDOMNodePtr pChild;

	// Grab Informations from the pObject node
	//
	this->Grab_Node_Informations(pObject);

	// Update "CurrentElementNode"
	//
	CurrentElementNode = pObject;

	// Call User Parse Handling for let him what he want.
	//
	this->Parse_XML_Document();

	if(!Is_MSXML_Node(pObject))
		return;

	// add the ChainTag
	//
	this->ChainTag_Add(this->Tag);

	for (pChild = pObject->firstChild;  NULL != pChild;  pChild = pChild->nextSibling)
	{
		// Parse Child nodes
		//
		this->Parse_Objects(pChild);
	}

	// Remove Current Tag from ChainTag
	//
	ChainTag_Remove(1);
}

bool XML_PARSER::Is_Tag(LPCTSTR aTag)
{ return this->Get_CurrentTag() == aTag; }

bool XML_PARSER::Is_TextNode()
{ return (this->Is_Tag("<#TEXT#>")); }

CString & XML_PARSER::Get_CurrentTag()
{	return this->Tag; }

CString & XML_PARSER::Get_CurrentName()
{  return this->Name; }

bool XML_PARSER::Is_Root()
{   return (this->ChainTag.IsEmpty() != 0); }

bool XML_PARSER::Is_Child_of(LPCTSTR parent_chain)
{
   	int pos = this->ChainTag.Find(parent_chain);
	int len = strlen(parent_chain);

	if(pos != -1)
	{	// look if it's the end of this chainTag
		//
		return ( this->ChainTag.GetLength() == pos + len );
	}

	return false;
}

CString & XML_PARSER::Get_TextValue()
{ return this->TextField; }

bool XML_PARSER::Is_MSXML_Node(IXMLDOMNodePtr pChild)
{  return (pChild->nodeType != NODE_TEXT); }

void XML_PARSER::Grab_Node_Informations(IXMLDOMNodePtr pChild)
{
	if(this->Is_MSXML_Node(pChild))
	{	// It's a node
		//

		// Tag Update
		//
		Tag.Format("<%s>",(const char*)(pChild->nodeName));
		Name = (const char*)(pChild->nodeName);

		// TextField no significant value
		TextField.Empty();

		// Update Attribute List
		//
		this->AttribNames.RemoveAll();
		this->AttribValues.RemoveAll();

		IXMLDOMNamedNodeMapPtr pAttribs = pChild->Getattributes();
		if(pAttribs != NULL)
		{ 	long nAttriCnt = pAttribs->Getlength();
			// Iterate over the attributes
			//
			for(int i=0; i<nAttriCnt; ++i)
			{  IXMLDOMNodePtr pAttrib = pAttribs->Getitem(i);
			   if(pAttrib != NULL)
			   {
					this->AttribNames.Add(	(CString)(const char *) pAttrib->GetnodeName() );

					_variant_t vVal = pAttrib->GetnodeValue ( );
					this->AttribValues.Add( (CString)(const char *) _bstr_t(vVal) );
			   }
			}
		}
	}
	else
	{   // Tag is #TEXT#
		//
		Tag.Empty();
		Tag = "<#TEXT#>";
		Name.Empty();
		Name = "#TEXT#";

		// TextField Update
		//
		TextField = (const char*)(pChild->text);

		// Update Attribute List have no means
		//
		this->AttribNames.RemoveAll();
		this->AttribValues.RemoveAll();
	}

	return;
}

void XML_PARSER::ChainTag_Add(CString & val)
{
		// Add a tag to the ChainTag
		//
		if(!ChainTag.IsEmpty())
			ChainTag += val;
		else
			ChainTag = val;
}

void XML_PARSER::ChainTag_Remove(int number)
{
		// Remove the n tag to the ChainTag
		//
		for(int bcl = 0; bcl < number; bcl ++)
		{
			int pos = ChainTag.ReverseFind('<');
			if(pos == -1)
				ChainTag.Empty();
			else
				ChainTag = ChainTag.Left(pos);
		}
}

bool XML_PARSER::Is_Having_Attribute(LPCTSTR Name)
{
   	// Create the CString Name Object
   	//
   	CString sName = Name;

   	// Clear attribute index
   	//
   	attrib_index = -1;

 	int bcl;
  	for(bcl = 0; bcl < this->AttribNames.GetSize() ; bcl++)
   	{	// Check if the name is equal
   		//
   		if(this->AttribNames[bcl] == sName)
   		{ // set index fot let user to retrieve value with "Get_Attribute_Value()" method
   		  //
   		  attrib_index = bcl;
   		  return true;
   		}
   	}
   	return false;
}

CString & XML_PARSER::Get_Attribute_Value()
{  // Assume Success
   //
   lasterror = ok;

   if(attrib_index != -1)
	 return this->AttribValues[attrib_index];

   // We can't retrieve a Attribute values
   //
   lasterror = "Can't Retrieve an Attribute";
   return lasterror;
}

bool XML_PARSER::Add_LastChildNode(LPCTSTR Name)
{
	// Nodes members
	// IXMLDOMElementPtr CurrentElementNode;	/* Global Member */
	//
	IXMLDOMNodePtr newNode;

	// Create NODE TYPE
	//
	CComVariant vType(MSXML::NODE_ELEMENT);

	// Create the NODE
	//
	newNode = m_plDomDocument->createNode(vType,Name,"");

	// Attach the Node to the document
	//
	if(CurrentElementNode != NULL)
	{	this->ChainTag_Add( this->Get_CurrentTag() );
		newNode = CurrentElementNode->appendChild(newNode);
	}
	else if(m_pDocRoot != NULL)
	{	this->ChainTag_Add( (CString)(const char*)m_pDocRoot->nodeName );
		newNode = m_pDocRoot->appendChild(newNode);
	}
	else
	{	this->ChainTag.Empty();
		m_pDocRoot = newNode;
		m_plDomDocument->documentElement = m_pDocRoot;
	}

	// Update Current Node (cast operation)
	//
	CurrentElementNode = newNode;

	// Update information for this Node
	//
	this->Grab_Node_Informations(CurrentElementNode);

	return true;
}

bool XML_PARSER::Add_NodeBefore(LPCTSTR Name)
{	// Nodes members
	// IXMLDOMElementPtr CurrentElementNode;	/* Global Member */
	//
	IXMLDOMNodePtr newNode;
	
	// Can't use this function on the root node
	//
	if(this->Is_Root())
		return false;
	// Create NODE TYPE
	//
	CComVariant vType(MSXML::NODE_ELEMENT);

	// Create the NODE
	//
	newNode = m_plDomDocument->createNode(vType,Name,"");

	if(this->Is_Root())
		return false;

	// Create Reference Node for the Insertion
	//
	IXMLDOMNodePtr pParent;
	this->CurrentElementNode->get_parentNode(&pParent);
	_variant_t NodeRef = (IUnknown *)CurrentElementNode;
	

	// Attach the Node to the document
	//
	if(CurrentElementNode != NULL)
		newNode = pParent->insertBefore(newNode,NodeRef);
	else if(m_pDocRoot != NULL)
		newNode = m_pDocRoot->insertBefore(newNode,NodeRef);
	else
	{	m_pDocRoot = newNode;
		m_plDomDocument->documentElement = m_pDocRoot;
	}

	// Update Current Node (cast operation)
	//
	CurrentElementNode = newNode;

	// Update information for this Node
	//
	this->Grab_Node_Informations(CurrentElementNode);

	return true;
}

bool XML_PARSER::Add_NodeAfter(LPCTSTR Name)
{	// Nodes members
	// IXMLDOMElementPtr CurrentElementNode;	/* Global Member */
	//
	IXMLDOMNodePtr newNode;
	
	// Can't use this function on the root node
	//
	if(this->Is_Root())
		return false;

	// Create NODE TYPE
	//
	CComVariant vType(MSXML::NODE_ELEMENT);

	// Create the NODE
	//
	newNode = m_plDomDocument->createNode(vType,Name,"");

	if(this->Is_Root())
		return false;

	// If CurrentElementNode->NextSibling == NULL then must call Add_LastChildNode on Parent Node
	// Because we can't use InsertBefore on a NULL Reference ;o)
	//
	// We are sure that a Parent node exist because before we control that we aren't not on root node.
	//
	if(CurrentElementNode->nextSibling == NULL)
	{	// Get Parent Node
		//
		IXMLDOMNodePtr pParent;
		this->CurrentElementNode->get_parentNode(&pParent);

		// Set Parent node as Current Node
		//
		this->CurrentElementNode = pParent;
		this->Grab_Node_Informations(pParent);

		// Add Node as Last Child Node
		//
		return (this->Add_LastChildNode(Name));
	}

	// Create Reference Node for the Insertion
	//
	IXMLDOMNodePtr pParent;
	this->CurrentElementNode->get_parentNode(&pParent);
	_variant_t NodeRef = (IUnknown *)CurrentElementNode->nextSibling;
	

	// Attach the Node to the document
	//
	if(CurrentElementNode != NULL)
		newNode = pParent->insertBefore(newNode,NodeRef);
	else if(m_pDocRoot != NULL)
		newNode = m_pDocRoot->insertBefore(newNode,NodeRef);
	else
	{	m_pDocRoot = newNode;
		m_plDomDocument->documentElement = m_pDocRoot;
	}

	// Update Current Node (cast operation)
	//
	CurrentElementNode = newNode;

	// Update information for this Node
	//
	this->Grab_Node_Informations(CurrentElementNode);

	return true;
}

bool XML_PARSER::Add_FirstChildNode(LPCTSTR Name)
{	// Nodes members
	// IXMLDOMElementPtr CurrentElementNode;	/* Global Member */
	//
	IXMLDOMNodePtr newNode;
	//IXMLDOMNodeListPtr ChildList;

	// If no child then use Add_LastChildNode or CurrentElement node not set yet
	//
	if(CurrentElementNode != NULL)
	{	if( !this->CurrentElementNode->hasChildNodes() )
			return (this->Add_LastChildNode(Name));
	}
	else
		return (this->Add_LastChildNode(Name)); 

	// Create NODE TYPE
	//
	CComVariant vType(MSXML::NODE_ELEMENT);

	// Create the NODE
	//
	newNode = m_plDomDocument->createNode(vType,Name,"");

	// Create Reference Node for the Insertion
	//
	_variant_t NodeRef = (IUnknown *)CurrentElementNode->firstChild;

	// Attach the Node to the document
	//
	if(CurrentElementNode != NULL)
	{	this->ChainTag_Add( this->Get_CurrentTag() );
		newNode = CurrentElementNode->insertBefore(newNode,NodeRef);
	}
	else if(m_pDocRoot != NULL)
	{	this->ChainTag_Add( (CString)(const char*)m_pDocRoot->nodeName );
		newNode = m_pDocRoot->insertBefore(newNode,NodeRef);
	}
	else
	{	this->ChainTag.Empty();
		m_pDocRoot = newNode;
		m_plDomDocument->documentElement = m_pDocRoot;
	}

	// Update Current Node (cast operation)
	//
	CurrentElementNode = newNode;

	// Update information for this Node
	//
	this->Grab_Node_Informations(CurrentElementNode);

	return true;
}

bool XML_PARSER::Set_Attribute(LPCTSTR AttribName,LPCTSTR AttribValue)
{
	// Nodes members
	// IXMLDOMElementPtr CurrentElementNode;	/* Global Member */
	//

	// Create Attribute variable
	//
	CComVariant sAttribute(AttribValue);

	// Set the new attribute
	//
	if(CurrentElementNode != NULL)
	{
		CurrentElementNode->setAttribute( AttribName, sAttribute );
		this->Grab_Node_Informations(CurrentElementNode);
	}
	else
	{	m_pDocRoot->setAttribute( AttribName, sAttribute );
		this->Grab_Node_Informations(m_pDocRoot);
	}

	// Return
	//
	return true;
}

bool XML_PARSER::Remove_Attribute(LPCTSTR AttribName)
{
	if(CurrentElementNode == NULL)
	{	if(this->m_pDocRoot != NULL)
			this->CurrentElementNode = this->m_pDocRoot;
		else
			return false;
	}

	this->CurrentElementNode->removeAttribute(AttribName);
	return true;
}

bool XML_PARSER::Set_Text(LPCTSTR TextValue)
{
	// Nodes members
	// IXMLDOMElementPtr CurrentElementNode;	/* Global Member */
	//
	IXMLDOMNodePtr newNode;

	// Create NODE TEXT type
	//
	CComVariant vType(MSXML::NODE_TEXT);

	// Create the node
	//
	newNode = m_plDomDocument->createTextNode(TextValue);

	// Find if a CHILD TEXT NODE exist or not
	//
	if(CurrentElementNode == NULL)
	{	if(this->m_pDocRoot != NULL)
			this->CurrentElementNode = this->m_pDocRoot;
		else
			return false;
	}

	if(this->CurrentElementNode->hasChildNodes())
	{	
		IXMLDOMNodePtr pChild;
		for(pChild = this->CurrentElementNode->firstChild; pChild != NULL; pChild = pChild->nextSibling)
		{	// Find it's a NODE TEXT
			//
			if(!this->Is_MSXML_Node(pChild))
			{	// A Text Node is found, Replace it now!!
				//
				this->CurrentElementNode->replaceChild(newNode,pChild);
				return true;
			}
		}
	}
		
	// No previous Text was defined before, we can add it.
	//

	// Attach the Node to the document
	//
	newNode = CurrentElementNode->appendChild(newNode);
	return true;
}

bool XML_PARSER::Save_XML_Document(LPCTSTR strFileName)
{
	// Save the XML document
	//
	m_plDomDocument->save(strFileName);

	// Return
	//
	return true;
}

void XML_PARSER::Reset_XML_Document()
{
	// Init
	//
	this->Init_MSXML();
	m_plDomDocument->loadXML("<?xml version=\"1.0\" standalone=\"yes\" ?>");
	m_pDocRoot = m_plDomDocument->documentElement;
	CurrentElementNode = NULL;

	// Init our members
	//
	this->AttribNames.RemoveAll();
	this->AttribValues.RemoveAll();
	this->Tag.Empty();
	this->Name.Empty();
	this->ChainTag.Empty();
	this->TextField.Empty();
	attrib_index = -1;

}

void XML_PARSER::Go_to_Root() 
{ this->CurrentElementNode = this->m_pDocRoot;
  this->ChainTag.Empty();
}

bool XML_PARSER::Go_to_Child(LPCTSTR NodeName)
{
	// Child node
	//
	IXMLDOMNodePtr pChild;

	if(!Is_MSXML_Node(this->CurrentElementNode))
		return false;

	ChainTag_Add(this->Get_CurrentTag());

	for (pChild = CurrentElementNode->firstChild;  NULL != pChild;  pChild = pChild->nextSibling)
	{
		// Grab Information from Child node
		//
		this->Grab_Node_Informations(pChild);

		if(this->Get_CurrentName() == NodeName)
		{	// Update new Position
			//
			this->CurrentElementNode = pChild;
			return true; 
		}
	}

	// Node Not Found (Restore Node informations)
	//
	this->ChainTag_Remove(1);
	this->Grab_Node_Informations(this->CurrentElementNode);
	return false;
}
	
bool XML_PARSER::Go_to_Parent(LPCTSTR NodeName)			
{
	// Parent node
	//
	IXMLDOMNodePtr pParent = NULL;
    IXMLDOMNodePtr oldCurrent = this->CurrentElementNode;
	
	if(!Is_MSXML_Node(this->CurrentElementNode))
		return false;

	if(this->CurrentElementNode == this->m_pDocRoot)
		return false;

	CString oldChainTag = this->ChainTag;

	
	this->CurrentElementNode->get_parentNode(&pParent);
	
	while (true)
	{	
		this->CurrentElementNode = pParent;
		this->ChainTag_Remove(1);
		this->Grab_Node_Informations(this->CurrentElementNode);
		if(this->Get_CurrentName() == NodeName)
			return true;

		if(this->CurrentElementNode == this->m_pDocRoot)
			break;

		this->CurrentElementNode->get_parentNode(&pParent);
	}
	
	// Parent not found
	//
	this->CurrentElementNode = oldCurrent;
	this->ChainTag = oldChainTag;
	this->Grab_Node_Informations(this->CurrentElementNode);
	return false;
}

// Go to a Node attached at the same Node than the Current Node (Forward sens)
//
bool XML_PARSER::Go_to_Forward(LPCTSTR NodeName)
{
	// Sibling node
	//
	IXMLDOMNodePtr pSibling = NULL;

	if(!Is_MSXML_Node(this->CurrentElementNode))
		return false;

	for (pSibling= CurrentElementNode;  true ;  pSibling = pSibling->nextSibling)
	{
		if(pSibling == NULL)
			break;

		// Grab Information from Sibling node
		//
		this->Grab_Node_Informations(pSibling);

		if(this->Get_CurrentName() == NodeName)
		{	// Update new Position
			//
			this->CurrentElementNode = pSibling;
			return true; 
		}
	}

	// Node Not Found (Restore Node informations)
	//
	this->Grab_Node_Informations(this->CurrentElementNode);
	return false;
}
	
bool XML_PARSER::Go_to_Back(LPCTSTR NodeName)
{
	// Sibling node
	//
	IXMLDOMNodePtr pSibling;

	if(!Is_MSXML_Node(this->CurrentElementNode))
		return false;

	for (pSibling = CurrentElementNode;  NULL != pSibling;  pSibling = pSibling->previousSibling)
	{
		// Grab Information from Sibling node
		//
		this->Grab_Node_Informations(pSibling);

		if(this->Get_CurrentName() == NodeName)
		{	// Update new Position
			//
			this->CurrentElementNode = pSibling;
			return true; 
		}
	}

	// Node Not Found (Restore Node informations)
	//
	this->Grab_Node_Informations(this->CurrentElementNode);
	return false;
}
	
bool XML_PARSER::Remove()
{	
	// Parent node
	//
	IXMLDOMNodePtr pParent= NULL;

	if(CurrentElementNode == NULL)
	{	if(this->m_pDocRoot != NULL)
			this->CurrentElementNode = this->m_pDocRoot;
		else
			return false;
	}

	if(this->CurrentElementNode != this->m_pDocRoot)
	{	this->CurrentElementNode->get_parentNode(&pParent);
		pParent->removeChild(this->CurrentElementNode);
		this->CurrentElementNode = pParent;
		this->Grab_Node_Informations(this->CurrentElementNode);
	}
	else
		this->Reset_XML_Document();

	return true;
}

bool XML_PARSER::RemoveChild(LPCTSTR NodeName)
{
	// Find the Child
	//
	if( this->Go_to_Child(NodeName) )
		return this->Remove(); 
	else
		return false;
}

