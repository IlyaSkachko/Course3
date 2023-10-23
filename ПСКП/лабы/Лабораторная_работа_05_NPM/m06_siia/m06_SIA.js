const nodemailer = require("nodemailer");

module.exports.send = async function (myEmail, password, email, message) {
    let transporter = nodemailer.createTransport({
        service: "Mail.ru",
        auth: {
            user: myEmail,
            pass: password
        }
    });

    let result = await transporter.sendMail({
        from: myEmail,
        to: email,
        subject: "I'm doing Lab5",
        text: message
    });

    return result;
}

