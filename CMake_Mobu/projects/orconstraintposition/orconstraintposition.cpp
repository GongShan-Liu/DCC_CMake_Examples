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

/**	\file	orconstraintposition.cxx
*	Library declarations.
*	Contains the basic routines to declare the DLL as a loadable
*	library.
*/

//--- SDK include
#include <fbsdk/fbsdk.h>

//--- Library declaration
FBLibraryDeclare( orconstraintposition )
{
	FBLibraryRegister( ORConstraintPosition	);
}
FBLibraryDeclareEnd;

/************************************************
 *	Library functions.
 ************************************************/
bool FBLibrary::LibInit()		{ return true; }
bool FBLibrary::LibOpen()		{ return true; }
bool FBLibrary::LibReady()		{ return true; }
bool FBLibrary::LibClose()		{ return true; }
bool FBLibrary::LibRelease()	{ return true; }

/**
*	\mainpage	Simple Positional Constraint
*	\section	intro	Introduction
*	The orconstraintposition sample code is a very basic constraint,
*	with no particular functionality for the moment. It shows the different
*	function calls that will be overloaded when developing a constraint,
*	and gives a basic idea of the real-time evaluation and deformation callbacks.
*	\section	walk	Walkthrough
*	Due to the complex nature of constraints, this walkthrough will
*	cover the very basics of a constraint, dealing with all of the non-intuitive
*	functions in the sample code.
*	\subsection	func1	FBCreate()
*	<ol>
*		<li>Add a reference group: "Constrained object";
*		<li>Set as a deformer with a customized UI;
*		<li>Send the animation nodes to NULL;
*		<li>The layout has not been created yet (to NULL);
*	</ol>
*	\subsection	func2	SetupAllAnimationNodes()
*	<ol>
*		<li>If there is a constrained object;
*		<li>Bind the object the deformation;
*		<li>Create the animation nodes (input/output);
*	</ol>
*	\subsection	func3	RemoveAllAnimationNodes()
*	<ol>
*		<li>If there is a constrained object;
*		<li>Removed the deformer bind from the object.
*	</ol>
*	\subsection	func4	AnimationNodeNotify()
*	<ol>
*		<li>Read the data from the input translation & scaling nodes;
*	</ol>
*	\subsection	func5	DeformerNotify()
*	<ol>
*		<li>Calculate the difference between the positions;
*		<li>Add delta to the displacement;
*		<li>Remove 6% of displacement;
*		<li>Change all the vertices to respect the constraint;
*		<li>Copy current position to old position.
*	</ol>
*	\subsection	func6	GetLayout()
*	<ol>
*		<li>Create new ConstraintLayout.
*	</ol>
*/
