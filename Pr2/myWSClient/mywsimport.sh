#!/usr/bin/env bash
java -jar  ../myWSServer/lib/jaxws-lib/jaxws-tools.jar -d ./bin -Xdebug -keep -s ./src-gen -verbose http://localhost:8888/supersquare?WSDL
