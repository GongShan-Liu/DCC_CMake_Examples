#ifndef __ORCONSTRAINT_POSITION_CONSTRAINT_H__
#define __ORCONSTRAINT_POSITION_CONSTRAINT_H__
/***************************************************************************************
 Autodesk(R) Open Reality(R) Samples
 
 (C) 2009 Autodesk, Inc. and/or its licensors
 All rights reserved.
 
 AUTODESK SOFTWARE LICENSE AGREEMENT
 Autodesk, Inc. licenses this Software to you only upon the condition that 
 you accept all of the terms contained in the Software License Agreement ("Agreement") 
 that is embedded in or that is delivered with this Software. By selecting 
 the "I ACCEPT" button at the end of the Agreement or by copying, installing, 
 uploading, accessing or using all or any portion of the Software you agree 
 to enter into the Agreement. A contract is then formed between Autodesk and 
 either you personally, if you acquire the Software for yourself, or the company 
 or other legal entity for which you are acquiring the software.
 
 AUTODESK, INC., MAKES NO WARRANTY, EITHER EXPRESS OR IMPLIED, INCLUDING BUT 
 NOT LIMITED TO ANY IMPLIED WARRANTIES OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR 
 PURPOSE REGARDING THESE MATERIALS, AND MAKES SUCH MATERIALS AVAILABLE SOLELY ON AN 
 "AS-IS" BASIS.
 
 IN NO EVENT SHALL AUTODESK, INC., BE LIABLE TO ANYONE FOR SPECIAL, COLLATERAL, 
 INCIDENTAL, OR CONSEQUENTIAL DAMAGES IN CONNECTION WITH OR ARISING OUT OF PURCHASE 
 OR USE OF THESE MATERIALS. THE SOLE AND EXCLUSIVE LIABILITY TO AUTODESK, INC., 
 REGARDLESS OF THE FORM OF ACTION, SHALL NOT EXCEED THE PURCHASE PRICE OF THE 
 MATERIALS DESCRIBED HEREIN.
 
 Autodesk, Inc., reserves the right to revise and improve its products as it sees fit.
 
 Autodesk and Open Reality are registered trademarks or trademarks of Autodesk, Inc., 
 in the U.S.A. and/or other countries. All other brand names, product names, or 
 trademarks belong to their respective holders. 
 
 GOVERNMENT USE
 Use, duplication, or disclosure by the U.S. Government is subject to restrictions as 
 set forth in FAR 12.212 (Commercial Computer Software-Restricted Rights) and 
 DFAR 227.7202 (Rights in Technical Data and Computer Software), as applicable. 
 Manufacturer is Autodesk, Inc., 10 Duke Street, Montreal, Quebec, Canada, H3C 2L7.
***************************************************************************************/

/**	\file	orconstraintposition_constraint.h
*	Declaration of a simple constraint class.
*	Simple constraint class declaration (FBSimpleConstraint).
*/

//--- SDK include
#include <fbsdk/fbsdk.h>

#define ORCONSTRAINTPOSITION__CLASSNAME		ORConstraintPosition
#define ORCONSTRAINTPOSITION__CLASSSTR		"ORConstraintPosition"

//! A simple constraint class.
class ORConstraintPosition : public FBConstraint
{
	//--- declaration
	FBConstraintDeclare( ORConstraintPosition, FBConstraint );

public:
	//--- Creation & Destruction
	virtual bool			FBCreate();							//!< Constructor.
	virtual void			FBDestroy();						//!< Destructor.

	//--- Animation node management
	virtual void			RemoveAllAnimationNodes();			//!< Remove animation nodes.
	virtual void			SetupAllAnimationNodes();			//!< Setup animation nodes.


	virtual void			FreezeSuggested		();				//!< Suggest 'freeze'.

	//! Real-time evaluation engine function.
	virtual bool			AnimationNodeNotify		( FBAnimationNode* pAnimationNode, FBEvaluateInfo* pEvaluateInfo, FBConstraintInfo* pConstraintInfo );

	//--- FBX Interface
	virtual bool			FbxStore	( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat );	//!< FBX Storage.
	virtual bool			FbxRetrieve	( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat );	//!< FBX Retrieval.

	//--- Local parameters
	FBAnimationNode*	mSourceTranslation;			//!< AnimationNode: INPUT  -> Source.
	FBAnimationNode*	mConstrainedTranslation;	//!< AnimationNode: OUTPUT -> Constraint.
	FBAnimationNode*	mDeformTranslation;			//!< AnimationNode: OUTPUT -> Translation.

	int					mGroupSource;		//!< Source groupe index.
	int					mGroupConstrain;	//!< Constraint group index.
	int					mGroupDeform;		//!< Deformation group index.

	FBTVector			mPosition;			//!< Position vector.
	FBTVector			mOldPosition;		//!< Old position vector.
	FBTVector			mDisplacement;		//!< Displacement vector.
	bool				mFirstTime;			//!< First time that the constraint is called?
	FBSVector			mScaling;			//!< Scaling vector.
};

#endif	/* __ORCONSTRAINT_POSITION_CONSTRAINT_H__ */
