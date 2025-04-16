grammar BDD;

document: feature+ EOF;

feature
    : FEATURE_HEADER NEWLINE scenario+
    ;

scenario
    : SCENARIO_HEADER NEWLINE step+
    ;

step
    : STEP_START NEWLINE
    ;

STEP_START
    : ('Given' | 'When' | 'Then' | 'And' | 'But') WS+ ~[\r\n]+
    ;

FEATURE_HEADER  : 'Feature:' ~[\r\n]*;
SCENARIO_HEADER : 'Scenario:' ~[\r\n]*;

NEWLINE : '\r'? '\n';
WS      : [ \t]+ -> skip;
