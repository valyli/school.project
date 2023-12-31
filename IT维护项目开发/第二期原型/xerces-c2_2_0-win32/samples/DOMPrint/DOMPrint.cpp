/*
 * The Apache Software License, Version 1.1
 *
 * Copyright (c) 2002 The Apache Software Foundation.  All rights
 * reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * 3. The end-user documentation included with the redistribution,
 *    if any, must include the following acknowledgment:
 *       "This product includes software developed by the
 *        Apache Software Foundation (http://www.apache.org/)."
 *    Alternately, this acknowledgment may appear in the software itself,
 *    if and wherever such third-party acknowledgments normally appear.
 *
 * 4. The names "Xerces" and "Apache Software Foundation" must
 *    not be used to endorse or promote products derived from this
 *    software without prior written permission. For written
 *    permission, please contact apache\@apache.org.
 *
 * 5. Products derived from this software may not be called "Apache",
 *    nor may "Apache" appear in their name, without prior written
 *    permission of the Apache Software Foundation.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED.  IN NO EVENT SHALL THE APACHE SOFTWARE FOUNDATION OR
 * ITS CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF
 * USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 * ====================================================================
 *
 * This software consists of voluntary contributions made by many
 * individuals on behalf of the Apache Software Foundation, and was
 * originally based on software copyright (c) 1999, International
 * Business Machines, Inc., http://www.ibm.com .  For more information
 * on the Apache Software Foundation, please see
 * <http://www.apache.org/>.
 */

/*
 * $Id: DOMPrint.cpp,v 1.54 2003/01/28 18:30:56 peiyongz Exp $
 */

// ---------------------------------------------------------------------------
//  This sample program invokes the XercesDOMParser to build a DOM tree for
//  the specified input file. It then invokes DOMWriter::writeNode() to
//  serialize the resultant DOM tree back to XML stream.
//
//  Note:
//  Application needs to provide its own implementation of
//		   DOMErrorHandler (in this sample, the DOMPrintErrorHandler),
//		   if it would like to receive notification from the serializer
//		   in the case any error occurs during the serialization.
//
//  Application needs to provide its own implementation of
//		   DOMWriterFilter (in this sample, the DOMPrintFilter),
//		   if it would like to filter out certain part of the DOM
//		   representation, but must be aware that thus may render the
//		   resultant XML stream invalid.
//
//  Application may choose any combination of characters as the
//		   end of line sequence to be used in the resultant XML stream,
//		   but must be aware that thus may render the resultant XML
//		   stream ill formed.
//
//  Application may choose a particular encoding name in which
//		   the output XML stream would be, but must be aware that if
//		   characters, unrepresentable in the encoding specified, appearing
//		   in markups, may force the serializer to terminate serialization
//		   prematurely, and thus no complete serialization would be done.
//
//  Application shall query the serializer first, before set any
//           feature/mode(true, false), or be ready to catch exception if this
//           feature/mode is not supported by the serializer.
//
//  Application needs to clean up the filter, error handler and
//		   format target objects created for the serialization.
//
//   Limitations:
//      1.  The encoding="xxx" clause in the XML header should reflect
//          the system local code page, but does not.
//      2.  Cases where the XML data contains characters that can not
//          be represented in the system local code page are not handled.
//
// ---------------------------------------------------------------------------


// ---------------------------------------------------------------------------
//  Includes
// ---------------------------------------------------------------------------
#include <xercesc/util/PlatformUtils.hpp>

#include <xercesc/dom/DOM.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationLS.hpp>
#include <xercesc/dom/DOMWriter.hpp>

#include <xercesc/framework/StdOutFormatTarget.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/parsers/XercesDOMParser.hpp>
#include <xercesc/util/XMLUni.hpp>

#include "DOMTreeErrorReporter.hpp"
#include "DOMPrintFilter.hpp"
#include "DOMPrintErrorHandler.hpp"

#include <string.h>
#include <stdlib.h>

// ---------------------------------------------------------------------------
//  Local data
//
//  gXmlFile
//      The path to the file to parser. Set via command line.
//
//  gDoNamespaces
//      Indicates whether namespace processing should be done.
//
//  gDoSchema
//      Indicates whether schema processing should be done.
//
//  gSchemaFullChecking
//      Indicates whether full schema constraint checking should be done.
//
//  gDoCreate
//      Indicates whether entity reference nodes needs to be created or not
//      Defaults to false
//
//  gOutputEncoding
//      The encoding we are to output in. If not set on the command line,
//      then it is defaults to the encoding of the input XML file.
//
//  gMyEOLSequence
//      The end of line sequence we are to output.
//
//  gSplitCdataSections
//      Indicates whether split-cdata-sections is to be enabled or not.
//
//  gDiscardDefaultContent
//      Indicates whether default content is discarded or not.
//
//  gUseFilter
//      Indicates if user wants to plug in the DOMPrintFilter.
//
//  gValScheme
//      Indicates what validation scheme to use. It defaults to 'auto', but
//      can be set via the -v= command.
//
// ---------------------------------------------------------------------------
static char*                    gXmlFile               = 0;
static bool                     gDoNamespaces          = false;
static bool                     gDoSchema              = false;
static bool                     gSchemaFullChecking    = false;
static bool                     gDoCreate              = false;

static char*                    goutputfile            = 0;
// options for DOMWriter's features
static const XMLCh*             gOutputEncoding        = 0;
static const XMLCh*             gMyEOLSequence         = 0;

static bool                     gSplitCdataSections    = true;
static bool                     gDiscardDefaultContent = true;
static bool                     gUseFilter             = false;
static bool                     gFormatPrettyPrint     = false;
static bool                     gWriteBOM              = false;

static XercesDOMParser::ValSchemes    gValScheme       = XercesDOMParser::Val_Auto;

// ---------------------------------------------------------------------------
//
//  Usage()
//
// ---------------------------------------------------------------------------
void usage()
{
    cout << "\nUsage:\n"
            "    DOMPrint [options] <XML file>\n\n"
            "This program invokes the DOM parser, and builds the DOM tree.\n"
            "It then asks the DOMWriter to serialize the DOM tree.\n"
            "Options:\n"
            "    -e          create entity reference nodes. Default is no expansion.\n"
            "    -v=xxx      Validation scheme [always | never | auto*].\n"
            "    -n          Enable namespace processing. Default is off.\n"
            "    -s          Enable schema processing. Default is off.\n"
            "    -f          Enable full schema constraint checking. Defaults is off.\n"
            "    -wenc=XXX   Use a particular encoding for output. Default is\n"
            "                the same encoding as the input XML file. UTF-8 if\n"
            "                input XML file has not XML declaration.\n"
            "    -weol=xxx   Set the end of line sequence. Default set by DOMWriter\n"
            "    -wfile=xxx  Write to a file instead of stdout.\n"
            "    -wscs=xxx   Enable/Disable split-cdata-sections.      Default on\n"
            "    -wddc=xxx   Enable/Disable discard-default-content.   Default on\n"
            "    -wflt=xxx   Enable/Disable filtering.                 Default off\n"
            "    -wfpp=xxx   Enable/Disable format-pretty-print.       Default off\n"
            "    -wbom=xxx   Enable/Disable write Byte-Order-Mark      Default off\n"
            "    -?          Show this help.\n\n"
            "  * = Default if not provided explicitly.\n\n"
            "The parser has intrinsic support for the following encodings:\n"
            "    UTF-8, USASCII, ISO8859-1, UTF-16[BL]E, UCS-4[BL]E,\n"
            "    WINDOWS-1252, IBM1140, IBM037.\n"
          <<  endl;
}

// ---------------------------------------------------------------------------
//
//  main
//
// ---------------------------------------------------------------------------
int main(int argC, char* argV[])
{
    int retval = 0;

    // Initialize the XML4C2 system
    try
    {
        XMLPlatformUtils::Initialize();
    }

    catch(const XMLException &toCatch)
    {
        cerr << "Error during Xerces-c Initialization.\n"
             << "  Exception message:"
             << StrX(toCatch.getMessage()) << endl;
        return 1;
    }

    // Check command line and extract arguments.
    if (argC < 2)
    {
        usage();
        XMLPlatformUtils::Terminate();
        return 1;
    }

    // See if non validating dom parser configuration is requested.
    int parmInd;
    for (parmInd = 1; parmInd < argC; parmInd++)
    {
        // Break out on first parm not starting with a dash
        if (argV[parmInd][0] != '-')
            break;

        // Watch for special case help request
        if (!strcmp(argV[parmInd], "-?"))
        {
            usage();
            XMLPlatformUtils::Terminate();
            return 2;
        }
         else if (!strncmp(argV[parmInd], "-v=", 3)
              ||  !strncmp(argV[parmInd], "-V=", 3))
        {
            const char* const parm = &argV[parmInd][3];

            if (!strcmp(parm, "never"))
                gValScheme = XercesDOMParser::Val_Never;
            else if (!strcmp(parm, "auto"))
                gValScheme = XercesDOMParser::Val_Auto;
            else if (!strcmp(parm, "always"))
                gValScheme = XercesDOMParser::Val_Always;
            else
            {
                cerr << "Unknown -v= value: " << parm << endl;
                XMLPlatformUtils::Terminate();
                return 2;
            }
        }
         else if (!strcmp(argV[parmInd], "-n")
              ||  !strcmp(argV[parmInd], "-N"))
        {
            gDoNamespaces = true;
        }
         else if (!strcmp(argV[parmInd], "-s")
              ||  !strcmp(argV[parmInd], "-S"))
        {
            gDoSchema = true;
        }
         else if (!strcmp(argV[parmInd], "-f")
              ||  !strcmp(argV[parmInd], "-F"))
        {
            gSchemaFullChecking = true;
        }
         else if (!strcmp(argV[parmInd], "-e")
              ||  !strcmp(argV[parmInd], "-E"))
        {
            gDoCreate = true;
        }
         else if (!strncmp(argV[parmInd], "-wenc=", 6))
        {
             // Get out the encoding name
             gOutputEncoding = XMLString::transcode( &(argV[parmInd][6]) );
        }
         else if (!strncmp(argV[parmInd], "-wfile=", 7))
        {
             goutputfile =  &(argV[parmInd][7]);
        }
         else if (!strncmp(argV[parmInd], "-weol=", 6))
        {
             // Get out the end of line
             gMyEOLSequence = XMLString::transcode( &(argV[parmInd][6]) );
        }			
         else if (!strncmp(argV[parmInd], "-wddc=", 6))
        {
            const char* const parm = &argV[parmInd][6];

            if (!strcmp(parm, "on"))
				gDiscardDefaultContent = true;
            else if (!strcmp(parm, "off"))
				gDiscardDefaultContent = false;
            else
            {
                cerr << "Unknown -wddc= value: " << parm << endl;
                XMLPlatformUtils::Terminate();
                return 2;
            }

        }
         else if (!strncmp(argV[parmInd], "-wscs=", 6))
        {
            const char* const parm = &argV[parmInd][6];

            if (!strcmp(parm, "on"))
				gSplitCdataSections = true;
			else if (!strcmp(parm, "off"))
				gSplitCdataSections = false;
            else
            {
                cerr << "Unknown -wscs= value: " << parm << endl;
                XMLPlatformUtils::Terminate();
                return 2;
            }
        }
         else if (!strncmp(argV[parmInd], "-wflt=", 6))
        {
            const char* const parm = &argV[parmInd][6];

            if (!strcmp(parm, "on"))
				gUseFilter = true;
			else if (!strcmp(parm, "off"))
				gUseFilter = false;
            else
            {
                cerr << "Unknown -wflt= value: " << parm << endl;
                XMLPlatformUtils::Terminate();
                return 2;
            }
        }
         else if (!strncmp(argV[parmInd], "-wfpp=", 6))
        {
            const char* const parm = &argV[parmInd][6];

            if (!strcmp(parm, "on"))
				gFormatPrettyPrint = true;
			else if (!strcmp(parm, "off"))
				gFormatPrettyPrint = false;
            else
            {
                cerr << "Unknown -wfpp= value: " << parm << endl;
                XMLPlatformUtils::Terminate();
                return 2;
            }
        }
         else if (!strncmp(argV[parmInd], "-wbom=", 6))
        {
            const char* const parm = &argV[parmInd][6];

            if (!strcmp(parm, "on"))
                gWriteBOM = true;
            else if (!strcmp(parm, "off"))
                gWriteBOM = false;
            else
            {
                cerr << "Unknown -wbom= value: " << parm << endl;
                XMLPlatformUtils::Terminate();
                return 2;
            }
        }
         else
        {
            cerr << "Unknown option '" << argV[parmInd]
                 << "', ignoring it.\n" << endl;
        }
    }

    //
    //  And now we have to have only one parameter left and it must be
    //  the file name.
    //
    if (parmInd + 1 != argC)
    {
        usage();
        XMLPlatformUtils::Terminate();
        return 1;
    }
    gXmlFile = argV[parmInd];

    //
    //  Create our parser, then attach an error handler to the parser.
    //  The parser will call back to methods of the ErrorHandler if it
    //  discovers errors during the course of parsing the XML document.
    //
    XercesDOMParser *parser = new XercesDOMParser;
    parser->setValidationScheme(gValScheme);
    parser->setDoNamespaces(gDoNamespaces);
    parser->setDoSchema(gDoSchema);
    parser->setValidationSchemaFullChecking(gSchemaFullChecking);
    parser->setCreateEntityReferenceNodes(gDoCreate);

    DOMTreeErrorReporter *errReporter = new DOMTreeErrorReporter();
    parser->setErrorHandler(errReporter);

    //
    //  Parse the XML file, catching any XML exceptions that might propogate
    //  out of it.
    //
    bool errorsOccured = false;
    try
    {
        parser->parse(gXmlFile);
    }

    catch (const XMLException& e)
    {
        cerr << "An error occurred during parsing\n   Message: "
             << StrX(e.getMessage()) << endl;
        errorsOccured = true;
    }

    catch (const DOMException& e)
    {
        const unsigned int maxChars = 2047;
        XMLCh errText[maxChars + 1];

        cerr << "\nDOM Error during parsing: '" << gXmlFile << "'\n"
             << "DOMException code is:  " << e.code << endl;

        if (DOMImplementation::loadDOMExceptionMsg(e.code, errText, maxChars))
             cerr << "Message is: " << StrX(errText) << endl;

        errorsOccured = true;
    }

    catch (...)
    {
        cerr << "An error occurred during parsing\n " << endl;
        errorsOccured = true;
    }

    // If the parse was successful, output the document data from the DOM tree
    if (!errorsOccured && !errReporter->getSawErrors())
    {
        DOMPrintFilter   *myFilter = 0;

        try
        {
            // get a serializer, an instance of DOMWriter
            XMLCh tempStr[100];
            XMLString::transcode("LS", tempStr, 99);
            DOMImplementation *impl          = DOMImplementationRegistry::getDOMImplementation(tempStr);
            DOMWriter         *theSerializer = ((DOMImplementationLS*)impl)->createDOMWriter();

            // set user specified end of line sequence and output encoding
            theSerializer->setNewLine(gMyEOLSequence);
            theSerializer->setEncoding(gOutputEncoding);

            // plug in user's own filter
            if (gUseFilter)
            {
                // even we say to show attribute, but the DOMWriter
                // will not show attribute nodes to the filter as
                // the specs explicitly says that DOMWriter shall
                // NOT show attributes to DOMWriterFilter.
                //
                // so DOMNodeFilter::SHOW_ATTRIBUTE has no effect.
                // same DOMNodeFilter::SHOW_DOCUMENT_TYPE, no effect.
                //
                myFilter = new DOMPrintFilter(DOMNodeFilter::SHOW_ELEMENT   |
                                              DOMNodeFilter::SHOW_ATTRIBUTE |
                                              DOMNodeFilter::SHOW_DOCUMENT_TYPE);
                theSerializer->setFilter(myFilter);
            }

            // plug in user's own error handler
            DOMErrorHandler *myErrorHandler = new DOMPrintErrorHandler();
            theSerializer->setErrorHandler(myErrorHandler);

            // set feature if the serializer supports the feature/mode
            if (theSerializer->canSetFeature(XMLUni::fgDOMWRTSplitCdataSections, gSplitCdataSections))
                theSerializer->setFeature(XMLUni::fgDOMWRTSplitCdataSections, gSplitCdataSections);

            if (theSerializer->canSetFeature(XMLUni::fgDOMWRTDiscardDefaultContent, gDiscardDefaultContent))
                theSerializer->setFeature(XMLUni::fgDOMWRTDiscardDefaultContent, gDiscardDefaultContent);

            if (theSerializer->canSetFeature(XMLUni::fgDOMWRTFormatPrettyPrint, gFormatPrettyPrint))
                theSerializer->setFeature(XMLUni::fgDOMWRTFormatPrettyPrint, gFormatPrettyPrint);

            if (theSerializer->canSetFeature(XMLUni::fgDOMWRTBOM, gWriteBOM))
                theSerializer->setFeature(XMLUni::fgDOMWRTBOM, gWriteBOM);

            //
            // Plug in a format target to receive the resultant
            // XML stream from the serializer.
            //
            // StdOutFormatTarget prints the resultant XML stream
            // to stdout once it receives any thing from the serializer.
            //
            XMLFormatTarget *myFormTarget;
            if (goutputfile)
                myFormTarget = new LocalFileFormatTarget(goutputfile);
            else
                myFormTarget = new StdOutFormatTarget();

            // get the DOM representation
            DOMNode                     *doc = parser->getDocument();

            //
            // do the serialization through DOMWriter::writeNode();
            //
            theSerializer->writeNode(myFormTarget, *doc);

            delete theSerializer;

            //
            // Filter, formatTarget and error handler
            // are NOT owned by the serializer.
            //
            delete myFormTarget;
            delete myErrorHandler;

            if (gUseFilter)
                delete myFilter;

        }
        catch (XMLException& e)
        {
            cerr << "An error occurred during creation of output transcoder. Msg is:"
                << endl
                << StrX(e.getMessage()) << endl;
            retval = 4;
        }

    }
    else
        retval = 4;

    //
    //  Clean up the error handler. The parser does not adopt handlers
    //  since they could be many objects or one object installed for multiple
    //  handlers.
    //
    delete errReporter;

    //
    //  Delete the parser itself.  Must be done prior to calling Terminate, below.
    //
    delete parser;

    // And call the termination method
    XMLPlatformUtils::Terminate();

    delete (void *)gOutputEncoding;        // const problems.
    delete (void *)gMyEOLSequence;         // const problems.

    return retval;
}

