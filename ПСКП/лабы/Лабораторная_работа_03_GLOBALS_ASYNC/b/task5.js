
function square(number) {
    return new Promise((resolve, reject) => {
        if (!isNaN(number)) {
            resolve(Math.pow(number, 2));
        } else {
            reject("Error - 2");
        }
    }); 
}

function cube(number) {
    return new Promise((resolve, reject) => {
        if (!isNaN(number)) {
            resolve(Math.pow(number, 3));
        } else {
            reject("Error - 3");
        }
    }); 
}

function fourth(number) {
    return new Promise((resolve, reject) => {
        if (!isNaN(number)) {
            resolve(Math.pow(number, 4));
        } else {
            reject("Error - 4");
        }
    }); 
}


Promise.all([square(3), cube(5), fourth(2)])
    .then(result => {
        console.log(result);
    })
    .catch(error => {
        console.log(error);
    });