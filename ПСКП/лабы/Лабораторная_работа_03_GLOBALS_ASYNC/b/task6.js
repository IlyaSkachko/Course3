
function square(number) {
    return new Promise((resolve, reject) => {
        if (!isNaN(number)) {
            setTimeout(() => {
                resolve(Math.pow(number, 2));
            }, 2000);

        } else {
            setTimeout(() => {
                reject("Error - 2");
            }, 2000);
        }
    }); 
}

function cube(number) {
    return new Promise((resolve, reject) => {
        if (!isNaN(number)) {
            setTimeout(() => {
                resolve(Math.pow(number, 2));
            }, 2000);
        } else {
            setTimeout(() => {
                reject("Error - 3");
            }, 2000);
        }
    }); 
}

function fourth(number) {
    return new Promise((resolve, reject) => {
        if (!isNaN(number)) {
            setTimeout(() => {
                resolve(Math.pow(number, 4));
            }, 2000);
        } else {
            setTimeout(() => {
                reject("Error - 4");
            }, 2000);
        }
    }); 
}


Promise.race([square(2), cube(3), fourth(2)])
    .then(result => {
        console.log(result);
    })
    .catch(error => {
        console.log(error);
    });

Promise.any([square("g"), cube(3), fourth(2)])
    .then(result => {
        console.log(result);
    })
    .catch(error => {
        console.log(error);
    });