const nodemailer = require("nodemailer");
    
// exports.send = async function (myEmail, password, email, message) {
//     let transporter = nodemailer.createTransport({
//         service: "Mail.ru",
//         auth: {
//             user: myEmail,
//             pass: password
//         }
//     });

//     let result = await transporter.sendMail({
//         from: myEmail,
//         to: email,
//         subject: "I'm doing Lab5",
//         text: message
//     });

//     return result;
// }


module.exports.send = async function (email, password, message) {
    let transporter = nodemailer.createTransport({
        service: "Mail.ru",
        auth: {
            user: email,
            pass: password
        }
    });

    let result = await transporter.sendMail({
        from: email,
        to: email,
        subject: "I'm doing Lab5",
        text: message
    });

    return result;
}



