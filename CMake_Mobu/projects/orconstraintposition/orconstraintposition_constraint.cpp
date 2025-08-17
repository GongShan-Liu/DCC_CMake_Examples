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

/**	\file	orconstraintposition_constraint.cxx
*	Definition of a simple constraint class.
*	Simple constraint function definitions for the ORConstraintPosition
*	class.
*/

//--- Class declarations
#include "orconstraintposition_constraint.h"

//--- Registration defines
#define	ORCONSTRAINTPOSITION__CLASS		ORCONSTRAINTPOSITION__CLASSNAME
#define ORCONSTRAINTPOSITION__NAME		"Position from Position"
#define ORCONSTRAINTPOSITION__LABEL		"TestOR - Position from Position"
#define ORCONSTRAINTPOSITION__DESC		"TestOR - Position from Position Constraint"

//--- implementation and registration
FBConstraintImplementation	(	ORCONSTRAINTPOSITION__CLASS		);
FBRegisterConstraint		(	ORCONSTRAINTPOSITION__NAME,
								ORCONSTRAINTPOSITION__CLASS,
								ORCONSTRAINTPOSITION__LABEL,
								ORCONSTRAINTPOSITION__DESC,
								FB_DEFAULT_SDK_ICON				);	// Icon filename (default=Open Reality icon)

/************************************************
 *	Creation function.
 ************************************************/
bool ORConstraintPosition::FBCreate()
{
	// Create reference groups
	mGroupSource	= ReferenceGroupAdd( "Source Object",	1 );
	mGroupConstrain	= ReferenceGroupAdd( "Constrain",		1 );

	mSourceTranslation		= NULL;
	mConstrainedTranslation = NULL;

	mFirstTime = true;

	return true;
}


/************************************************
 *	Destruction function.
 ************************************************/
void ORConstraintPosition::FBDestroy()
{
}


/************************************************
 *	Setup all of the animation nodes.
 ************************************************/
void ORConstraintPosition::SetupAllAnimationNodes()
{
	if (ReferenceGet( mGroupSource, 0 ) && ReferenceGet( mGroupConstrain, 0 ) )
	{
		mSourceTranslation		= AnimationNodeOutCreate( 0, ReferenceGet( mGroupSource,	0 ), ANIMATIONNODE_TYPE_TRANSLATION );
		mConstrainedTranslation = AnimationNodeInCreate	( 1, ReferenceGet( mGroupConstrain, 0 ), ANIMATIONNODE_TYPE_TRANSLATION );
	}
}


/************************************************
 *	Removed all of the animation nodes.
 ************************************************/
void ORConstraintPosition::RemoveAllAnimationNodes()
{
}


/************************************************
 *	FBX storage of constraint parameters.
 ************************************************/
bool ORConstraintPosition::FbxStore( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat )
{
	return true;
}


/************************************************
 *	FBX retrieval of constraint parameters.
 ************************************************/
bool ORConstraintPosition::FbxRetrieve( FBFbxObject* pFbxObject, kFbxObjectStore pStoreWhat )
{
	return true;
}


/************************************************
 *	Suggest a freeze.
 ************************************************/
void ORConstraintPosition::FreezeSuggested()
{
	mFirstTime = true;
	FBConstraint::FreezeSuggested();

	if( ReferenceGet( 0,0 ) )
	{
		FreezeSRT( (FBModel*)ReferenceGet( 0, 0), true, true, true );
	}
}


/************************************************
 *	Real-Time Engine Evaluation
 ************************************************/
bool ORConstraintPosition::AnimationNodeNotify(FBAnimationNode* pConnector,FBEvaluateInfo* pEvaluateInfo,FBConstraintInfo* pConstraintInfo)
{
	double lPosition[3];

	if( mSourceTranslation && mConstrainedTranslation )
	{
		mSourceTranslation->ReadData		( lPosition, pEvaluateInfo );
		mConstrainedTranslation->WriteData	( lPosition, pEvaluateInfo );
	}
	mPosition = lPosition;

	return true;
}
