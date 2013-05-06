
package supersquare;

import java.net.MalformedURLException;
import java.net.URL;
import javax.xml.namespace.QName;
import javax.xml.ws.Service;
import javax.xml.ws.WebEndpoint;
import javax.xml.ws.WebServiceClient;
import javax.xml.ws.WebServiceException;
import javax.xml.ws.WebServiceFeature;


/**
 * This class was generated by the JAX-WS RI.
 * JAX-WS RI 2.2.4-b01
 * Generated source version: 2.2
 * 
 */
@WebServiceClient(name = "SuperSquareService", targetNamespace = "http://supersquare/", wsdlLocation = "http://localhost:8888/supersquare?wsdl")
public class SuperSquareService
    extends Service
{

    private final static URL SUPERSQUARESERVICE_WSDL_LOCATION;
    private final static WebServiceException SUPERSQUARESERVICE_EXCEPTION;
    private final static QName SUPERSQUARESERVICE_QNAME = new QName("http://supersquare/", "SuperSquareService");

    static {
        URL url = null;
        WebServiceException e = null;
        try {
            url = new URL("http://localhost:8888/supersquare?wsdl");
        } catch (MalformedURLException ex) {
            e = new WebServiceException(ex);
        }
        SUPERSQUARESERVICE_WSDL_LOCATION = url;
        SUPERSQUARESERVICE_EXCEPTION = e;
    }

    public SuperSquareService() {
        super(__getWsdlLocation(), SUPERSQUARESERVICE_QNAME);
    }

    public SuperSquareService(WebServiceFeature... features) {
        super(__getWsdlLocation(), SUPERSQUARESERVICE_QNAME, features);
    }

    public SuperSquareService(URL wsdlLocation) {
        super(wsdlLocation, SUPERSQUARESERVICE_QNAME);
    }

    public SuperSquareService(URL wsdlLocation, WebServiceFeature... features) {
        super(wsdlLocation, SUPERSQUARESERVICE_QNAME, features);
    }

    public SuperSquareService(URL wsdlLocation, QName serviceName) {
        super(wsdlLocation, serviceName);
    }

    public SuperSquareService(URL wsdlLocation, QName serviceName, WebServiceFeature... features) {
        super(wsdlLocation, serviceName, features);
    }

    /**
     * 
     * @return
     *     returns SuperSquare
     */
    @WebEndpoint(name = "SuperSquarePort")
    public SuperSquare getSuperSquarePort() {
        return super.getPort(new QName("http://supersquare/", "SuperSquarePort"), SuperSquare.class);
    }

    /**
     * 
     * @param features
     *     A list of {@link javax.xml.ws.WebServiceFeature} to configure on the proxy.  Supported features not in the <code>features</code> parameter will have their default values.
     * @return
     *     returns SuperSquare
     */
    @WebEndpoint(name = "SuperSquarePort")
    public SuperSquare getSuperSquarePort(WebServiceFeature... features) {
        return super.getPort(new QName("http://supersquare/", "SuperSquarePort"), SuperSquare.class, features);
    }

    private static URL __getWsdlLocation() {
        if (SUPERSQUARESERVICE_EXCEPTION!= null) {
            throw SUPERSQUARESERVICE_EXCEPTION;
        }
        return SUPERSQUARESERVICE_WSDL_LOCATION;
    }

}