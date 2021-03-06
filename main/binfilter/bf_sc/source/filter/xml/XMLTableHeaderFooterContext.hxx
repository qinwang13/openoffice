/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/


#ifndef _SC_XMLTABLEHEADERFOOTERCONTEXT_HXX_
#define _SC_XMLTABLEHEADERFOOTERCONTEXT_HXX_


#ifndef _XMLOFF_XMLICTXT_HXX_
#include <bf_xmloff/xmlictxt.hxx>
#endif

#ifndef _XMLOFF_XMLIMP_HXX_
#include <bf_xmloff/xmlimp.hxx>
#endif
#ifndef _COM_SUN_STAR_SHEET_XHEADERFOOTERCONTENT_HPP_
#include <com/sun/star/sheet/XHeaderFooterContent.hpp>
#endif
namespace binfilter {

namespace com { namespace sun { namespace star {
	namespace text { class XTextCursor; }
	namespace beans { class XPropertySet; }
} } }

class XMLTableHeaderFooterContext: public SvXMLImportContext
{
	::com::sun::star::uno::Reference <
		::com::sun::star::text::XTextCursor > xTextCursor;
	::com::sun::star::uno::Reference <
		::com::sun::star::text::XTextCursor > xOldTextCursor;
	::com::sun::star::uno::Reference <
		::com::sun::star::beans::XPropertySet > xPropSet;
	::com::sun::star::uno::Reference <
		::com::sun::star::sheet::XHeaderFooterContent > xHeaderFooterContent;

	const ::rtl::OUString	sOn;
	const ::rtl::OUString	sShareContent;
	const ::rtl::OUString	sContent;
	const ::rtl::OUString	sContentLeft;
	const ::rtl::OUString	sEmpty;
	::rtl::OUString			sCont;

	sal_Bool	bDisplay : 1;
	sal_Bool	bInsertContent : 1;
	sal_Bool 	bLeft : 1;
	sal_Bool	bContainsLeft : 1;
	sal_Bool	bContainsRight : 1;
	sal_Bool	bContainsCenter : 1;

public:
	TYPEINFO();

	XMLTableHeaderFooterContext( SvXMLImport& rImport, sal_uInt16 nPrfx,
			const ::rtl::OUString& rLName,
		    const ::com::sun::star::uno::Reference<
					::com::sun::star::xml::sax::XAttributeList > & xAttrList,
			const ::com::sun::star::uno::Reference <
		   			::com::sun::star::beans::XPropertySet > & rPageStylePropSet,
			   sal_Bool bFooter, sal_Bool bLft );

	virtual ~XMLTableHeaderFooterContext();

	virtual SvXMLImportContext *CreateChildContext(
			sal_uInt16 nPrefix,
			const ::rtl::OUString& rLocalName,
			const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList > & xAttrList );

	virtual void EndElement();
};

class XMLHeaderFooterRegionContext: public SvXMLImportContext
{
private:
	::com::sun::star::uno::Reference <
		::com::sun::star::text::XTextCursor >& xTextCursor;
	::com::sun::star::uno::Reference <
		::com::sun::star::text::XTextCursor > xOldTextCursor;

public:
	TYPEINFO();

	XMLHeaderFooterRegionContext( SvXMLImport& rImport, sal_uInt16 nPrfx,
			const ::rtl::OUString& rLName,
		    const ::com::sun::star::uno::Reference<
					::com::sun::star::xml::sax::XAttributeList > & xAttrList,
			::com::sun::star::uno::Reference< ::com::sun::star::text::XTextCursor >& xCursor );

	virtual ~XMLHeaderFooterRegionContext();

	virtual SvXMLImportContext *CreateChildContext(
			sal_uInt16 nPrefix,
			const ::rtl::OUString& rLocalName,
			const ::com::sun::star::uno::Reference< ::com::sun::star::xml::sax::XAttributeList > & xAttrList );

	virtual void EndElement();
};


} //namespace binfilter
#endif
