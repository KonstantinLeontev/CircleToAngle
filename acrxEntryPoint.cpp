// (C) Copyright 2002-2012 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.
//

//-----------------------------------------------------------------------------
//----- acrxEntryPoint.cpp
//-----------------------------------------------------------------------------
#include "StdAfx.h"
#include "resource.h"

//-----------------------------------------------------------------------------
#define szRDS _RXST("")

//-----------------------------------------------------------------------------
//----- ObjectARX EntryPoint
class CCircleToAngleApp : public AcRxArxApp {

public:
	CCircleToAngleApp () : AcRxArxApp () {}

	virtual AcRx::AppRetCode On_kInitAppMsg (void *pkt) {
		// TODO: Load dependencies here

		// You *must* call On_kInitAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kInitAppMsg (pkt) ;
		
		// TODO: Add your initialization code here

		return (retCode) ;
	}

	virtual AcRx::AppRetCode On_kUnloadAppMsg (void *pkt) {
		// TODO: Add your code here

		// You *must* call On_kUnloadAppMsg here
		AcRx::AppRetCode retCode =AcRxArxApp::On_kUnloadAppMsg (pkt) ;

		// TODO: Unload dependencies here

		return (retCode) ;
	}

	virtual void RegisterServerComponents () {
	}
	
	// The ACED_ARXCOMMAND_ENTRY_AUTO macro can be applied to any static member 
	// function of the CCircleToAngleApp class.
	// The function should take no arguments and return nothing.
	//
	// NOTE: ACED_ARXCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid and
	// have arguments to define context and command mechanism.
	
	// ACED_ARXCOMMAND_ENTRY_AUTO(classname, group, globCmd, locCmd, cmdFlags, UIContext)
	// ACED_ARXCOMMAND_ENTRYBYID_AUTO(classname, group, globCmd, locCmdId, cmdFlags, UIContext)
	// only differs that it creates a localized name using a string in the resource file
	//   locCmdId - resource ID for localized command

	// Modal Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(CCircleToAngleApp, MyGroup, MyCommand, MyCommandLocal, ACRX_CMD_MODAL)
	static void MyGroupMyCommand () {
		// Put your command code here

	}

	// Modal Command with pickfirst selection
	// ACED_ARXCOMMAND_ENTRY_AUTO(CCircleToAngleApp, MyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET)
	static void MyGroupMyPickFirst () {
		ads_name result ;
		int iRet =acedSSGet (ACRX_T("_I"), NULL, NULL, NULL, result) ;
		if ( iRet == RTNORM )
		{
			// There are selected entities
			// Put your command using pickfirst set code here
		}
		else
		{
			// There are no selected entities
			// Put your command code here
		}
	}

	// Application Session Command with localized name
	// ACED_ARXCOMMAND_ENTRY_AUTO(CCircleToAngleApp, MyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION)
	static void MyGroupMySessionCmd () {
		// Put your command code here
	}

	// The ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO macros can be applied to any static member 
	// function of the CCircleToAngleApp class.
	// The function may or may not take arguments and have to return RTNORM, RTERROR, RTCAN, RTFAIL, RTREJ to AutoCAD, but use
	// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal to return
	// a value to the Lisp interpreter.
	//
	// NOTE: ACED_ADSFUNCTION_ENTRY_AUTO / ACED_ADSCOMMAND_ENTRY_AUTO has overloads where you can provide resourceid.
	
	//- ACED_ADSFUNCTION_ENTRY_AUTO(classname, name, regFunc) - this example
	//- ACED_ADSSYMBOL_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file
	//- ACED_ADSCOMMAND_ENTRY_AUTO(classname, name, regFunc) - a Lisp command (prefix C:)
	//- ACED_ADSCOMMAND_ENTRYBYID_AUTO(classname, name, nameId, regFunc) - only differs that it creates a localized name using a string in the resource file

	// Lisp Function is similar to ARX Command but it creates a lisp 
	// callable function. Many return types are supported not just string
	// or integer.
	// ACED_ADSFUNCTION_ENTRY_AUTO(CCircleToAngleApp, MyLispFunction, false)
	static int ads_MyLispFunction () {
		//struct resbuf *args =acedGetArgs () ;
		
		// Put your command code here

		//acutRelRb (args) ;
		
		// Return a value to the AutoCAD Lisp Interpreter
		// acedRetNil, acedRetT, acedRetVoid, acedRetInt, acedRetReal, acedRetStr, acedRetPoint, acedRetName, acedRetList, acedRetVal

		return (RTNORM) ;
	}

	//-----------------------------------------------------------------------------
	// Test assignment.
	//-----------------------------------------------------------------------------
	
	// Task 5.1. Create a circle with arbitrary radius.
	static void CircleToAngle_BUILDCIRCLE(void) {
		// Get the current database.
		Acad::ErrorStatus es;
		AcDbBlockTable* pBlockTable;

		// Get the block table.
		if ((es = acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead)) != Acad::eOk) {
			acutPrintf(_T("\nCouldn't open the block table!"));
			delete pBlockTable;
			return;
		}

		// Add a new block table record.
		AcDbBlockTableRecord* pBTRec = new AcDbBlockTableRecord;
		if ((es = pBlockTable->getAt(ACDB_MODEL_SPACE, pBTRec, AcDb::kForWrite)) != Acad::eOk) {
			acutPrintf(_T("\nCouldn't add the block table record!"));
			delete pBTRec;
			delete pBlockTable;
			return;
		}
		pBlockTable->close();

		// Build a circle and append it to the model space block table record.
		// Declare a center of the circle and radius.
		ads_point pointCenter;
		double dRadius;

		// Get the center point of the circle.
		if (RTNORM != acedGetPoint(NULL, _T("Specify center point  for circle: "), pointCenter)) {
			return;
		}

		// Get the radius of the circle.
		if (RTNORM != acedGetReal(_T("\nEnter a radius of the circle: "), &dRadius)) {
			return;
		}

		AcDbCircle* pCircle = new AcDbCircle;
		pCircle->setCenter(AcGePoint3d(pointCenter[0], pointCenter[1], pointCenter[2]));
		pCircle->setRadius(dRadius);

		// Append to the database.
		AcDbObjectId circleId;
		if ((es = pBTRec->appendAcDbEntity(circleId, pCircle)) != Acad::eOk) {
			delete pCircle;
			pBTRec->close();
			return;
		}
		pBTRec->close();
		pCircle->close();
	}

	// Task 5.2. Create two lines by three points.
	static void CircleToAngle_LINE3POINTS(void) {
		// Get the current database.
		Acad::ErrorStatus es;
		AcDbBlockTable* pBlockTable;

		// Get the block table.
		if ((es = acdbHostApplicationServices()->workingDatabase()->getBlockTable(pBlockTable, AcDb::kForRead)) != Acad::eOk) {
			acutPrintf(_T("\nCouldn't open the block table!"));
			delete pBlockTable;
			return;
		}

		// Add a new block table record.
		AcDbBlockTableRecord* pBTRec = new AcDbBlockTableRecord;
		if ((es = pBlockTable->getAt(ACDB_MODEL_SPACE, pBTRec, AcDb::kForWrite)) != Acad::eOk) {
			acutPrintf(_T("\nCouldn't add the block table record!"));
			delete pBTRec;
			delete pBlockTable;
			return;
		}
		pBlockTable->close();

		// Build two lines and append them to the model space of the block table record.
		// Pt2 - is a shared point.
		ads_point Pt1, Pt2, Pt3;

		// Get the points.
		if (RTNORM != acedGetPoint(NULL, _T("Specify Pt1 point: "), Pt1)) {
			return;
		}

		if (RTNORM != acedGetPoint(NULL, _T("Specify Pt2 point: "), Pt2)) {
			return;
		}

		if (RTNORM != acedGetPoint(NULL, _T("Specify Pt3 point: "), Pt3)) {
			return;
		}

		// Create line 1.
		AcDbLine* pLine1 = new AcDbLine(AcGePoint3d(Pt1[0], Pt1[1], Pt1[2]), AcGePoint3d(Pt2[0], Pt2[1], Pt2[2]));
		// Append to the database.
		AcDbObjectId lineId1;
		if ((es = pBTRec->appendAcDbEntity(lineId1, pLine1)) != Acad::eOk) {
			delete pLine1;
			pBTRec->close();
			return;
		}

		// Create line 2.
		AcDbLine* pLine2 = new AcDbLine(AcGePoint3d(Pt2[0], Pt2[1], Pt2[2]), AcGePoint3d(Pt3[0], Pt3[1], Pt3[2]));
		AcDbObjectId lineId2;
		if ((es = pBTRec->appendAcDbEntity(lineId2, pLine2)) != Acad::eOk) {
			delete pLine1;
			delete pLine2;
			pBTRec->close();
			return;
		}

		// Clean up the pointers.
		pBTRec->close();
		pLine1->close();
		pLine2->close();
	}

	// Entity selection for task 5.3.
	static AcDbEntity* selectEntity(const ACHAR* prompt, AcDbObjectId& id, AcGePoint3d& pick, AcDb::OpenMode openMode) {
		AcDbEntity* pEntity = NULL;
		ads_name adsName;

		// Prompts the user to select an entity by specifying a point.
		if (acedEntSel(prompt, adsName, asDblArray(pick)) == RTNORM) {
			// Get the object's Id of the entity.
			AcDbObjectId objectId;
			if (acdbGetObjectId(objectId, adsName) == Acad::eOk) {
				// Get pointer to selected entity.
				AcDbEntity* pEntity;
				if (acdbOpenAcDbEntity(pEntity, objectId, AcDb::kForRead) == Acad::eOk) {
					return pEntity;
				}
			}
		}

		return pEntity;
	}

	// Close entities for task 5.3.
	static void cleanUpEntities(AcDbEntity* pEntity1, AcDbEntity* pEntity2 = NULL, AcDbEntity* pEntity3 = NULL) {
		if (pEntity1 != NULL) {
			pEntity1->close();
		}
		if (pEntity2 != NULL) {
			pEntity2->close();
		}
		if (pEntity3 != NULL) {
			pEntity3->close();
		}
	}

	// Task 5.3. Fit selected circle to an angle given by two lines.
	static void CircleToAngle_CIRCLETOANGLE(void) {

		AcDbEntity* pEntityCircle = NULL;
		AcDbEntity* pEntityLine1 = NULL;
		AcDbEntity* pEntityLine2 = NULL;
		AcGePoint3d ptPick;
		AcDbObjectId objectId;
		Acad::ErrorStatus es;
		AcGePoint3dArray ptArr;

		// Circle
		//---------------------------------------------------------

		// Get a circle.
		if ((pEntityCircle = selectEntity(_T("Select a circle: \n"), objectId, ptPick, AcDb::kForRead)) == NULL) {
			acutPrintf(L"\nSelection failed!");
			return;
		}
			
		// Check if it's an actually circle.
		AcDbCircle* pCircle;
		if ((pCircle = AcDbCircle::cast(pEntityCircle)) == NULL) {
			acutPrintf(L"\nSelected entity is not a circle!");
			cleanUpEntities(pEntityCircle);
			return;
		}
		// Get the circle's center point.
		AcGePoint3d pntSourceCenter;
		pntSourceCenter = pCircle->center();
		// Get the circle's radius.
		double dRadius;
		dRadius = pCircle->radius();

		// Line 1
		//---------------------------------------------------------

		// Get the first line.
		if ((pEntityLine1 = selectEntity(_T("Select the first line: \n"), objectId, ptPick, AcDb::kForRead)) == NULL) {
			acutPrintf(_T("\nSelection failed!"));
			cleanUpEntities(pEntityCircle);
			return;
		}

		// Check if it's an actually line.
		AcDbLine* pLine1;
		if ((pLine1 = AcDbLine::cast(pEntityLine1)) == NULL) {
			acutPrintf(_T("\nSelected entity is not a line!"));
			cleanUpEntities(pEntityCircle, pEntityLine1);
			return;
		}

		// Line 2
		//---------------------------------------------------------

		// Get the second line.
		if ((pEntityLine2 = selectEntity(_T("Select the second line: \n"), objectId, ptPick, AcDb::kForRead)) == NULL) {
			acutPrintf(_T("\nSelection failed!"));
			cleanUpEntities(pEntityCircle, pEntityLine1);
			return;
		}

		// Check if it's an actually line.
		AcDbLine* pLine2;
		if ((pLine2 = AcDbLine::cast(pEntityLine2)) == NULL) {
			acutPrintf(_T("\nSelected entity is not a line!"));
			cleanUpEntities(pEntityCircle, pEntityLine1, pEntityLine2);
			return;
		}

		// Get an intersection point.
		//---------------------------------------------------------

		// Fill AcGePoint3dArray with coordinates of the intersection point.
		if ((es = pEntityLine1->intersectWith(pEntityLine2, AcDb::kOnBothOperands, ptArr)) != Acad::eOk) {
			acutPrintf(_T("\nIntersection failed!"), acadErrorStatusText(es));
			cleanUpEntities(pEntityCircle, pEntityLine1, pEntityLine2);
			return;
		}

		// Get coordinates from array.
		AcGePoint3d pntIntersection;
		pntIntersection = (AcGePoint3d)(ptArr[0], ptArr[1], ptArr[2]);

		// Compute a center point of inscribed circle with given radius.
		//---------------------------------------------------------

		// Get vectors from lines.
		AcGeVector3d vec1 = (pLine1->startPoint() - pLine1->endPoint());
		vec1 = vec1.normalize();
		AcGeVector3d vec2 = (pLine2->startPoint() - pLine2->endPoint());
		vec2 = vec2.normalize();
		// Get a half of an angle between them.
		double dAngle = vec1.angleTo(vec1) / 2;
		// Get a distance to destination point.
		double dDistance = dRadius / sin(dAngle);
		// Get a vector from angle vertex to destination point.
		AcGeVector3d vecBisect = (vec1 + vec2) * dDistance;
		// Get the destination circle point.
		AcGePoint3d pntDestCenter = pntIntersection.setToSum(pntIntersection, vecBisect);

		// Move selected circle to those point.
		//---------------------------------------------------------

		// Get vector from source to destination point.
		AcGeVector3d vecTransform = AcGeVector3d(pntSourceCenter[0], pntSourceCenter[1], pntSourceCenter[2]) + AcGeVector3d(pntDestCenter[0], pntDestCenter[1], pntDestCenter[2]);
		pEntityCircle->transformBy(vecTransform);

		// Clean up pointers.
		cleanUpEntities(pEntityCircle, pEntityLine1, pEntityLine2);
	}
} ;

//-----------------------------------------------------------------------------
IMPLEMENT_ARX_ENTRYPOINT(CCircleToAngleApp)

ACED_ARXCOMMAND_ENTRY_AUTO(CCircleToAngleApp, MyGroup, MyCommand, MyCommandLocal, ACRX_CMD_MODAL, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CCircleToAngleApp, MyGroup, MyPickFirst, MyPickFirstLocal, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CCircleToAngleApp, MyGroup, MySessionCmd, MySessionCmdLocal, ACRX_CMD_MODAL | ACRX_CMD_SESSION, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CCircleToAngleApp, CircleToAngle, _BUILDCIRCLE, BUILDCIRCLE, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CCircleToAngleApp, CircleToAngle, _LINE3POINTS, LINE3POINTS, ACRX_CMD_TRANSPARENT, NULL)
ACED_ARXCOMMAND_ENTRY_AUTO(CCircleToAngleApp, CircleToAngle, _CIRCLETOANGLE, CIRCLETOANGLE, ACRX_CMD_MODAL | ACRX_CMD_USEPICKSET, NULL)
ACED_ADSSYMBOL_ENTRY_AUTO(CCircleToAngleApp, MyLispFunction, false)

