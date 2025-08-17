//**************************************************************************/
// Copyright (c) 1998-2018 Autodesk, Inc.
// All rights reserved.
// 
// Use of this software is subject to the terms of the Autodesk license 
// agreement provided at the time of installation or download, or which 
// otherwise accompanies this software in either electronic or hard copy form.
//**************************************************************************/
// DESCRIPTION: Appwizard generated plugin
// AUTHOR: 
//***************************************************************************/

#include "TestMeshObj.h"

#define TestMeshObj_CLASS_ID Class_ID(0x8411ad39, 0xb5fa1267)

#define PBLOCK_REF 0

class TestMeshObj : public SimpleObject2
{
public:
	// Constructor/Destructor
	TestMeshObj();
	virtual ~TestMeshObj();

	// Parameter block handled by parent

	// From BaseObject
	virtual CreateMouseCallBack* GetCreateMouseCallBack() override;

	// From Object
	virtual BOOL                 HasUVW() override;
	virtual void                 SetGenUVW(BOOL sw) override;
	virtual int                  CanConvertToType(Class_ID obtype) override;
	virtual Object*              ConvertToType(TimeValue t, Class_ID obtype) override;
	virtual void                 GetCollapseTypes(Tab<Class_ID>& clist,Tab<TSTR*>& nlist) override;
	virtual int                  IntersectRay(TimeValue t, Ray& ray, float& at, Point3& norm) override;

	// From Animatable
	virtual void                 BeginEditParams(IObjParam  *ip, ULONG flags,Animatable *prev) override;
	virtual void                 EndEditParams(IObjParam *ip, ULONG flags,Animatable *next) override;

	// From SimpleObject
	virtual void                 BuildMesh(TimeValue t) override;
	virtual void                 InvalidateUI() override;

	// From Animatable
	virtual Class_ID             ClassID() override             { return TestMeshObj_CLASS_ID; }
	virtual SClass_ID            SuperClassID() override        { return GEOMOBJECT_CLASS_ID; }
	virtual void                 GetClassName(TSTR& s) override { s = GetString(IDS_CLASS_NAME); }

	virtual RefTargetHandle      Clone(RemapDir& remap) override;

	virtual int                  NumParamBlocks() override              { return 1; } // Return number of ParamBlocks in this instance
	virtual IParamBlock2*        GetParamBlock(int /*i*/) override      { return pblock2; } // Return i'th ParamBlock
	virtual IParamBlock2*        GetParamBlockByID(BlockID id) override { return (pblock2->ID() == id) ? pblock2 : NULL; } // Return id'd ParamBlock

	virtual void                 DeleteThis() override { delete this; }
};



class TestMeshObjClassDesc : public ClassDesc2 
{
public:
	virtual int           IsPublic() override                       { return TRUE; }
	virtual void*         Create(BOOL /*loading = FALSE*/) override { return new TestMeshObj(); }
	virtual const TCHAR * ClassName() override                      { return GetString(IDS_CLASS_NAME); }
	virtual SClass_ID     SuperClassID() override                   { return GEOMOBJECT_CLASS_ID; }
	virtual Class_ID      ClassID() override                        { return TestMeshObj_CLASS_ID; }
	virtual const TCHAR*  Category() override                       { return GetString(IDS_CATEGORY); }

	virtual const TCHAR*  InternalName() override                   { return _T("TestMeshObj"); } // Returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE     HInstance() override                      { return hInstance; } // Returns owning module handle


};

ClassDesc2* GetTestMeshObjDesc()
{
	static TestMeshObjClassDesc TestMeshObjDesc;
	return &TestMeshObjDesc; 
}







static ParamBlockDesc2 testmeshobj_param_blk ( testmeshobj_params, _T("params"),  0, GetTestMeshObjDesc(), 
	P_AUTO_CONSTRUCT + P_AUTO_UI, PBLOCK_REF,
	// rollout
	IDD_PANEL, IDS_PARAMS, 0, 0, NULL,
	// params
	pb_spin,            _T("spin"),         TYPE_FLOAT,     P_ANIMATABLE,   IDS_SPIN,
		p_default,      0.1f,
		p_range,        0.0f, 1000.0f,
		p_ui,           TYPE_SPINNER,       EDITTYPE_FLOAT, IDC_EDIT,       IDC_SPIN,   0.01f,
		p_end,
	p_end
);




//--- TestMeshObj -------------------------------------------------------

TestMeshObj::TestMeshObj()
{
	GetTestMeshObjDesc()->MakeAutoParamBlocks(this);
}

TestMeshObj::~TestMeshObj()
{
}

void TestMeshObj::BeginEditParams(IObjParam* ip, ULONG flags, Animatable* prev)
{
	SimpleObject2::BeginEditParams(ip,flags,prev);
	GetTestMeshObjDesc()->BeginEditParams(ip, this, flags, prev);
}

void TestMeshObj::EndEditParams(IObjParam* ip, ULONG flags, Animatable* next)
{
	// TODO: Save plugin parameter values into class variables, if they are not hosted in ParamBlocks.
	SimpleObject2::EndEditParams(ip,flags,next);
	GetTestMeshObjDesc()->EndEditParams(ip, this, flags, next);
}

// From Object
BOOL TestMeshObj::HasUVW() 
{ 
	// TODO: Return whether the object has UVW coordinates or not
	return TRUE; 
}

void TestMeshObj::SetGenUVW(BOOL sw) 
{
	if (sw==HasUVW()) 
	return;
	// TODO: Set the plugin's internal value to sw
}

// Class for interactive creation of the object using the mouse
class TestMeshObjCreateCallBack : public CreateMouseCallBack {
	IPoint2 sp0; // First point in screen coordinates
	TestMeshObj* ob; // Pointer to the object 
	Point3 p0; // First point in world coordinates
public:
	int  proc(ViewExp *vpt,int msg, int point, int flags, IPoint2 m, Matrix3& mat);
	void SetObj(TestMeshObj *obj) { ob = obj; }
};

int TestMeshObjCreateCallBack::proc(ViewExp *vpt,int msg, int point, int /*flags*/, IPoint2 m, Matrix3& mat)
{
	// TODO: Implement the mouse creation code here
	if ( ! vpt || ! vpt->IsAlive() )
	{
		// Why are we here
		DbgAssert(!_T("Invalid viewport!"));
		return FALSE;
	}

	if (msg == MOUSE_POINT || msg == MOUSE_MOVE) {
		switch(point) {
		case 0: // Only happens with MOUSE_POINT msg
			ob->suspendSnap = TRUE;
			sp0 = m;
			p0 = vpt->SnapPoint(m,m,NULL,SNAP_IN_PLANE);
			mat.SetTrans(p0);
			break;
		// TODO: Add for the rest of points
		}
	} else {
		if (msg == MOUSE_ABORT) return CREATE_ABORT;
	}

	return TRUE;
}

static TestMeshObjCreateCallBack TestMeshObjCreateCB;

// From BaseObject
CreateMouseCallBack* TestMeshObj::GetCreateMouseCallBack() 
{
	TestMeshObjCreateCB.SetObj(this);
	return(&TestMeshObjCreateCB);
}

// From SimpleObject
void TestMeshObj::BuildMesh(TimeValue /*t*/)
{
	// TODO: Implement the code to build the mesh representation of the object
	//       using its parameter settings at the time passed. The plug-in should 
	//       use the data member mesh to store the built mesh.
	//       SimpleObject ivalid member should be updated. This can be done while
	//       retrieving values from pblock2.
	ivalid = FOREVER;
}

void TestMeshObj::InvalidateUI() 
{
	// Hey! Update the param blocks
	pblock2->GetDesc()->InvalidateUI();
}

Object* TestMeshObj::ConvertToType(TimeValue t, Class_ID obtype)
{
	// TODO: If the plugin can convert to a nurbs surface then check to see 
	//       whether obtype == EDITABLE_SURF_CLASS_ID and convert the object
	//       to nurbs surface and return the object
	//       If no special conversion is needed remove this implementation.
	
	return __super::ConvertToType(t,obtype);
}

int TestMeshObj::CanConvertToType(Class_ID obtype)
{
	// TODO: Check for any additional types the plugin supports
	//       If no special conversion is needed remove this implementation.
	return __super::CanConvertToType(obtype);
}

// From Object
int TestMeshObj::IntersectRay(TimeValue /*t*/, Ray& /*ray*/, float& /*at*/, Point3& /*norm*/)
{
	// TODO: Return TRUE after you implement this method
	return FALSE;
}

void TestMeshObj::GetCollapseTypes(Tab<Class_ID>& clist,Tab<TSTR*>& nlist)
{
	Object::GetCollapseTypes(clist, nlist);
	// TODO: Append any any other collapse type the plugin supports
}

// From ReferenceTarget
RefTargetHandle TestMeshObj::Clone(RemapDir& remap) 
{
	TestMeshObj* newob = new TestMeshObj();
	// TODO: Make a copy all the data and also clone all the references
	newob->ReplaceReference(0,remap.CloneRef(pblock2));
	newob->ivalid.SetEmpty();
	BaseClone(this, newob, remap);
	return(newob);
}
