# Generated from /Users/leonardorocha/CLionProjects/pi-cluster-control/bdd/BDD.g4 by ANTLR 4.13.0
from antlr4 import *
if "." in __name__:
    from .BDDParser import BDDParser
else:
    from BDDParser import BDDParser

# This class defines a complete listener for a parse tree produced by BDDParser.
class BDDListener(ParseTreeListener):

    # Enter a parse tree produced by BDDParser#document.
    def enterDocument(self, ctx:BDDParser.DocumentContext):
        pass

    # Exit a parse tree produced by BDDParser#document.
    def exitDocument(self, ctx:BDDParser.DocumentContext):
        pass


    # Enter a parse tree produced by BDDParser#feature.
    def enterFeature(self, ctx:BDDParser.FeatureContext):
        pass

    # Exit a parse tree produced by BDDParser#feature.
    def exitFeature(self, ctx:BDDParser.FeatureContext):
        pass


    # Enter a parse tree produced by BDDParser#scenario.
    def enterScenario(self, ctx:BDDParser.ScenarioContext):
        pass

    # Exit a parse tree produced by BDDParser#scenario.
    def exitScenario(self, ctx:BDDParser.ScenarioContext):
        pass


    # Enter a parse tree produced by BDDParser#step.
    def enterStep(self, ctx:BDDParser.StepContext):
        pass

    # Exit a parse tree produced by BDDParser#step.
    def exitStep(self, ctx:BDDParser.StepContext):
        pass



del BDDParser