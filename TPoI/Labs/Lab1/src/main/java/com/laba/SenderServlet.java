package com.laba;

import com.sun.messaging.ConnectionConfiguration;
import com.sun.messaging.ConnectionFactory;

import javax.annotation.Resource;
import javax.jms.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.io.IOException;
import java.io.PrintWriter;

@WebServlet(name = "SenderServlet", value = "/SenderServlet")
public class SenderServlet extends HttpServlet {

    /*@Resource(lookup ="DefaultJMSConnectionFactory")
    private ConnectionFactory factory;

    @Resource(lookup = "Servlet")
    private Destination consumer;*/

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        ConnectionFactory factory = new ConnectionFactory();

        try (JMSContext context = factory.createContext("admin", "admin")){
            factory.setProperty(ConnectionConfiguration.imqAddressList, "mq://127.0.0.1:7676, mq://127.0.0.1:7676");

            Destination cardsQueue = context.createQueue("Servlet");
            JMSProducer producer = context.createProducer();

            producer.send(cardsQueue, request.getParameter("message"));

            System.out.println("Placed an information about card transaction to BankCardQueue");
        }
        catch (JMSException err) {
            System.out.println(err.getMessage());
        }

        response.sendRedirect("");
    }
}
