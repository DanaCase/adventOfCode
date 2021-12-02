fs = require('fs');

const input = fs.readFileSync('./2input.txt', {encoding: 'utf-8'});
let passwords = input.split('\n');
passwords.pop();
passwords.pop();
let totalCounts = 0;

passwords.forEach((password, i) => {
    const parts = password.split(' ');
    const rule1 = parts[0];
    const rule2 = parts[1].split('')[0];
    const pass = parts[2];

    const positions = rule1.split("-");
    const two = +positions[1];
    const one = +positions[0];

    if(pass[one - 1] === rule2) {
        if(pass[two - 1] !== rule2) {
            totalCounts++;
        }
    } else if (pass[two - 1] === rule2) {
        totalCounts++;
    }

})

console.log('totalCounts', totalCounts);
