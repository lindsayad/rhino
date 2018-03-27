//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html
#include "RhinoTestApp.h"
#include "RhinoApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "MooseSyntax.h"
#include "ModulesApp.h"

template <>
InputParameters
validParams<RhinoTestApp>()
{
  InputParameters params = validParams<RhinoApp>();
  return params;
}

RhinoTestApp::RhinoTestApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  RhinoApp::registerObjectDepends(_factory);
  RhinoApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  RhinoApp::associateSyntaxDepends(_syntax, _action_factory);
  RhinoApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  RhinoApp::registerExecFlags(_factory);

  bool use_test_objs = getParam<bool>("allow_test_objects");
  if (use_test_objs)
  {
    RhinoTestApp::registerObjects(_factory);
    RhinoTestApp::associateSyntax(_syntax, _action_factory);
    RhinoTestApp::registerExecFlags(_factory);
  }
}

RhinoTestApp::~RhinoTestApp() {}

void
RhinoTestApp::registerApps()
{
  registerApp(RhinoApp);
  registerApp(RhinoTestApp);
}

void
RhinoTestApp::registerObjects(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new test objects here! */
}

void
RhinoTestApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
  /* Uncomment Syntax and ActionFactory parameters and register your new test objects here! */
}

void
RhinoTestApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execute flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
// External entry point for dynamic application loading
extern "C" void
RhinoTestApp__registerApps()
{
  RhinoTestApp::registerApps();
}

// External entry point for dynamic object registration
extern "C" void
RhinoTestApp__registerObjects(Factory & factory)
{
  RhinoTestApp::registerObjects(factory);
}

// External entry point for dynamic syntax association
extern "C" void
RhinoTestApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  RhinoTestApp::associateSyntax(syntax, action_factory);
}

// External entry point for dynamic execute flag loading
extern "C" void
RhinoTestApp__registerExecFlags(Factory & factory)
{
  RhinoTestApp::registerExecFlags(factory);
}
