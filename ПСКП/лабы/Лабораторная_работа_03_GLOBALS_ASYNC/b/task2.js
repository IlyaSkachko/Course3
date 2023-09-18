

function secondJob() {
    return new Promise((resolve, reject) => {
        setTimeout(() => {
            reject("secondJob");
        }, 3000)
    });
}

secondJob()
    .then((result) => {console.log(result)})
    .catch(error => {
        console.log(error);
    });

async function secondJobAsync() {
    try {
        console.log(await secondJob());
    } catch(error) {
        console.log(error  + " async");
    }
}

secondJobAsync();