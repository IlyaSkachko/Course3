const uuid = require("uuid");

function createOrder(cardNumber) {
    let orderId;
    return new Promise((resolve, reject) => {
        if (validateCard(cardNumber)) {
            reject("Card is not valid");
        } else {
            setTimeout(() => {
                resolve(uuid.v4());
            }, 5000);
        }
    });
}

function validateCard(cardNumber) {
    console.log("Card number: " + cardNumber);
    return Math.random() < 0.5;
}

function proceedToPayment(orderId) {
    console.log("Order ID: " + orderId);
    return new Promise((resolve, reject) => {
        const isSuccess = Math.random() < 0.5;
        setTimeout(() => {
            if (isSuccess) {
                resolve("Payment successful");
            } else {
                reject(new Error("Payment failed"));
            }
        }, 1000);
    });
}

createOrder("1234 5678 9123 4567")
    .then((result) => {
        proceedToPayment(result);
    })
    .catch((error) => {
        console.log(error);
    });

async function processOrder() {
    try {
        console.log(
            await proceedToPayment(await createOrder("1234 5678 9123 456"))
        );
    } catch (error) {
        console.log(error);
    }
}

processOrder();
