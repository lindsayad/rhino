#include "RhinoApp.h"
#include "Moose.h"
#include "AppFactory.h"
#include "ModulesApp.h"
#include "MooseSyntax.h"

template <>
InputParameters
validParams<RhinoApp>()
{
  InputParameters params = validParams<MooseApp>();
  return params;
}

RhinoApp::RhinoApp(InputParameters parameters) : MooseApp(parameters)
{
  Moose::registerObjects(_factory);
  ModulesApp::registerObjects(_factory);
  RhinoApp::registerObjects(_factory);

  Moose::associateSyntax(_syntax, _action_factory);
  ModulesApp::associateSyntax(_syntax, _action_factory);
  RhinoApp::associateSyntax(_syntax, _action_factory);

  Moose::registerExecFlags(_factory);
  ModulesApp::registerExecFlags(_factory);
  RhinoApp::registerExecFlags(_factory);
}

RhinoApp::~RhinoApp() {}

void
RhinoApp::registerApps()
{
  registerApp(RhinoApp);
}

void
RhinoApp::registerObjects(Factory & factory)
{
    Registry::registerObjectsTo(factory, {"RhinoApp"});
}

void
RhinoApp::associateSyntax(Syntax & /*syntax*/, ActionFactory & action_factory)
{
  Registry::registerActionsTo(action_factory, {"RhinoApp"});

  /* Uncomment Syntax parameter and register your new production objects here! */
}

void
RhinoApp::registerObjectDepends(Factory & /*factory*/)
{
}

void
RhinoApp::associateSyntaxDepends(Syntax & /*syntax*/, ActionFactory & /*action_factory*/)
{
}

void
RhinoApp::registerExecFlags(Factory & /*factory*/)
{
  /* Uncomment Factory parameter and register your new execution flags here! */
}

/***************************************************************************************************
 *********************** Dynamic Library Entry Points - DO NOT MODIFY ******************************
 **************************************************************************************************/
extern "C" void
RhinoApp__registerApps()
{
  RhinoApp::registerApps();
}

extern "C" void
RhinoApp__registerObjects(Factory & factory)
{
  RhinoApp::registerObjects(factory);
}

extern "C" void
RhinoApp__associateSyntax(Syntax & syntax, ActionFactory & action_factory)
{
  RhinoApp::associateSyntax(syntax, action_factory);
}

extern "C" void
RhinoApp__registerExecFlags(Factory & factory)
{
  RhinoApp::registerExecFlags(factory);
}
