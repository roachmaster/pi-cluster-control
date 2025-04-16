# Generated from /Users/leonardorocha/CLionProjects/pi-cluster-control/bdd/BDD.g4 by ANTLR 4.13.0
# encoding: utf-8
from antlr4 import *
from io import StringIO
import sys
if sys.version_info[1] > 5:
	from typing import TextIO
else:
	from typing.io import TextIO

def serializedATN():
    return [
        4,1,5,33,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,1,0,4,0,10,8,0,11,0,12,
        0,11,1,0,1,0,1,1,1,1,1,1,4,1,19,8,1,11,1,12,1,20,1,2,1,2,1,2,4,2,
        26,8,2,11,2,12,2,27,1,3,1,3,1,3,1,3,0,0,4,0,2,4,6,0,0,31,0,9,1,0,
        0,0,2,15,1,0,0,0,4,22,1,0,0,0,6,29,1,0,0,0,8,10,3,2,1,0,9,8,1,0,
        0,0,10,11,1,0,0,0,11,9,1,0,0,0,11,12,1,0,0,0,12,13,1,0,0,0,13,14,
        5,0,0,1,14,1,1,0,0,0,15,16,5,2,0,0,16,18,5,4,0,0,17,19,3,4,2,0,18,
        17,1,0,0,0,19,20,1,0,0,0,20,18,1,0,0,0,20,21,1,0,0,0,21,3,1,0,0,
        0,22,23,5,3,0,0,23,25,5,4,0,0,24,26,3,6,3,0,25,24,1,0,0,0,26,27,
        1,0,0,0,27,25,1,0,0,0,27,28,1,0,0,0,28,5,1,0,0,0,29,30,5,1,0,0,30,
        31,5,4,0,0,31,7,1,0,0,0,3,11,20,27
    ]

class BDDParser ( Parser ):

    grammarFileName = "BDD.g4"

    atn = ATNDeserializer().deserialize(serializedATN())

    decisionsToDFA = [ DFA(ds, i) for i, ds in enumerate(atn.decisionToState) ]

    sharedContextCache = PredictionContextCache()

    literalNames = [  ]

    symbolicNames = [ "<INVALID>", "STEP_START", "FEATURE_HEADER", "SCENARIO_HEADER", 
                      "NEWLINE", "WS" ]

    RULE_document = 0
    RULE_feature = 1
    RULE_scenario = 2
    RULE_step = 3

    ruleNames =  [ "document", "feature", "scenario", "step" ]

    EOF = Token.EOF
    STEP_START=1
    FEATURE_HEADER=2
    SCENARIO_HEADER=3
    NEWLINE=4
    WS=5

    def __init__(self, input:TokenStream, output:TextIO = sys.stdout):
        super().__init__(input, output)
        self.checkVersion("4.13.0")
        self._interp = ParserATNSimulator(self, self.atn, self.decisionsToDFA, self.sharedContextCache)
        self._predicates = None




    class DocumentContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def EOF(self):
            return self.getToken(BDDParser.EOF, 0)

        def feature(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(BDDParser.FeatureContext)
            else:
                return self.getTypedRuleContext(BDDParser.FeatureContext,i)


        def getRuleIndex(self):
            return BDDParser.RULE_document

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterDocument" ):
                listener.enterDocument(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitDocument" ):
                listener.exitDocument(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitDocument" ):
                return visitor.visitDocument(self)
            else:
                return visitor.visitChildren(self)




    def document(self):

        localctx = BDDParser.DocumentContext(self, self._ctx, self.state)
        self.enterRule(localctx, 0, self.RULE_document)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 9 
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while True:
                self.state = 8
                self.feature()
                self.state = 11 
                self._errHandler.sync(self)
                _la = self._input.LA(1)
                if not (_la==2):
                    break

            self.state = 13
            self.match(BDDParser.EOF)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class FeatureContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def FEATURE_HEADER(self):
            return self.getToken(BDDParser.FEATURE_HEADER, 0)

        def NEWLINE(self):
            return self.getToken(BDDParser.NEWLINE, 0)

        def scenario(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(BDDParser.ScenarioContext)
            else:
                return self.getTypedRuleContext(BDDParser.ScenarioContext,i)


        def getRuleIndex(self):
            return BDDParser.RULE_feature

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterFeature" ):
                listener.enterFeature(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitFeature" ):
                listener.exitFeature(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitFeature" ):
                return visitor.visitFeature(self)
            else:
                return visitor.visitChildren(self)




    def feature(self):

        localctx = BDDParser.FeatureContext(self, self._ctx, self.state)
        self.enterRule(localctx, 2, self.RULE_feature)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 15
            self.match(BDDParser.FEATURE_HEADER)
            self.state = 16
            self.match(BDDParser.NEWLINE)
            self.state = 18 
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while True:
                self.state = 17
                self.scenario()
                self.state = 20 
                self._errHandler.sync(self)
                _la = self._input.LA(1)
                if not (_la==3):
                    break

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class ScenarioContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def SCENARIO_HEADER(self):
            return self.getToken(BDDParser.SCENARIO_HEADER, 0)

        def NEWLINE(self):
            return self.getToken(BDDParser.NEWLINE, 0)

        def step(self, i:int=None):
            if i is None:
                return self.getTypedRuleContexts(BDDParser.StepContext)
            else:
                return self.getTypedRuleContext(BDDParser.StepContext,i)


        def getRuleIndex(self):
            return BDDParser.RULE_scenario

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterScenario" ):
                listener.enterScenario(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitScenario" ):
                listener.exitScenario(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitScenario" ):
                return visitor.visitScenario(self)
            else:
                return visitor.visitChildren(self)




    def scenario(self):

        localctx = BDDParser.ScenarioContext(self, self._ctx, self.state)
        self.enterRule(localctx, 4, self.RULE_scenario)
        self._la = 0 # Token type
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 22
            self.match(BDDParser.SCENARIO_HEADER)
            self.state = 23
            self.match(BDDParser.NEWLINE)
            self.state = 25 
            self._errHandler.sync(self)
            _la = self._input.LA(1)
            while True:
                self.state = 24
                self.step()
                self.state = 27 
                self._errHandler.sync(self)
                _la = self._input.LA(1)
                if not (_la==1):
                    break

        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx


    class StepContext(ParserRuleContext):
        __slots__ = 'parser'

        def __init__(self, parser, parent:ParserRuleContext=None, invokingState:int=-1):
            super().__init__(parent, invokingState)
            self.parser = parser

        def STEP_START(self):
            return self.getToken(BDDParser.STEP_START, 0)

        def NEWLINE(self):
            return self.getToken(BDDParser.NEWLINE, 0)

        def getRuleIndex(self):
            return BDDParser.RULE_step

        def enterRule(self, listener:ParseTreeListener):
            if hasattr( listener, "enterStep" ):
                listener.enterStep(self)

        def exitRule(self, listener:ParseTreeListener):
            if hasattr( listener, "exitStep" ):
                listener.exitStep(self)

        def accept(self, visitor:ParseTreeVisitor):
            if hasattr( visitor, "visitStep" ):
                return visitor.visitStep(self)
            else:
                return visitor.visitChildren(self)




    def step(self):

        localctx = BDDParser.StepContext(self, self._ctx, self.state)
        self.enterRule(localctx, 6, self.RULE_step)
        try:
            self.enterOuterAlt(localctx, 1)
            self.state = 29
            self.match(BDDParser.STEP_START)
            self.state = 30
            self.match(BDDParser.NEWLINE)
        except RecognitionException as re:
            localctx.exception = re
            self._errHandler.reportError(self, re)
            self._errHandler.recover(self, re)
        finally:
            self.exitRule()
        return localctx





