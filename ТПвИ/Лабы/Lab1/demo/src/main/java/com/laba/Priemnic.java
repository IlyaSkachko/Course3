package com.laba;

import com.sun.messaging.ConnectionConfiguration;
import com.sun.messaging.ConnectionFactory;

import javax.jms.*;

public class Priemnic implements MessageListener {

    ConnectionFactory factory = new com.sun.messaging.ConnectionFactory();
    JMSConsumer consumer;
    public Priemnic() {
        try (JMSContext context = factory.createContext("admin", "admin")) {
            factory.setProperty(ConnectionConfiguration.imqAddressList,
                    "mq://127.0.0.1:7676,mq://127.0.0.1:7676");
            Destination cardsQueue = (Destination) context.createQueue("Servlet");

            consumer = context.createConsumer(cardsQueue);

            consumer.setMessageListener(this);

            System.out.println("Listening to servlet...");

            // wait for messages
            Thread.sleep(100000);
        } catch (InterruptedException | JMSException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }

    @Override
    public void onMessage(Message message) {
        try{
            System.out.println("Message from servlet: " + message.getBody(String.class));
        } catch (JMSException e){
            System.err.println("JMSException: " + e.toString());
        }
    }

    public static void main(String[] args) {
        new Priemnic();
    }
}
