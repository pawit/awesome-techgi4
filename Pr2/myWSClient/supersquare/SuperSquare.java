
package supersquare;

import javax.jws.WebMethod;
import javax.jws.WebParam;
import javax.jws.WebResult;
import javax.jws.WebService;
import javax.xml.bind.annotation.XmlSeeAlso;
import javax.xml.ws.RequestWrapper;
import javax.xml.ws.ResponseWrapper;


/**
 * This class was generated by the JAX-WS RI.
 * JAX-WS RI 2.2.4-b01
 * Generated source version: 2.2
 * 
 */
@WebService(name = "SuperSquare", targetNamespace = "http://supersquare/")
@XmlSeeAlso({
    ObjectFactory.class
})
public interface SuperSquare {


    /**
     * 
     * @param arg0
     * @return
     *     returns int
     */
    @WebMethod
    @WebResult(targetNamespace = "")
    @RequestWrapper(localName = "calcSquare", targetNamespace = "http://supersquare/", className = "supersquare.CalcSquare")
    @ResponseWrapper(localName = "calcSquareResponse", targetNamespace = "http://supersquare/", className = "supersquare.CalcSquareResponse")
    public int calcSquare(
        @WebParam(name = "arg0", targetNamespace = "")
        int arg0);

}
