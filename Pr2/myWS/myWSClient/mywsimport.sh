#!/usr/bin/env bash
java -jar  ~/2013/mylibs/jaxws-tools.jar -d ./bin -Xdebug -keep -s ./src-gen -verbose http://localhost:8080/WebServiceExample/circlefunctions?WSDL
