# Generated from /Users/leonardorocha/CLionProjects/pi-cluster-control/bdd/BDD.g4 by ANTLR 4.13.0
from antlr4 import *
if "." in __name__:
    from .BDDParser import BDDParser
else:
    from BDDParser import BDDParser

# This class defines a complete generic visitor for a parse tree produced by BDDParser.

class BDDVisitor(ParseTreeVisitor):

    # Visit a parse tree produced by BDDParser#document.
    def visitDocument(self, ctx:BDDParser.DocumentContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by BDDParser#feature.
    def visitFeature(self, ctx:BDDParser.FeatureContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by BDDParser#scenario.
    def visitScenario(self, ctx:BDDParser.ScenarioContext):
        return self.visitChildren(ctx)


    # Visit a parse tree produced by BDDParser#step.
    def visitStep(self, ctx:BDDParser.StepContext):
        return self.visitChildren(ctx)



del BDDParser