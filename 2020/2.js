fs = require('fs');

const input = fs.readFileSync('./2input.txt', {encoding: 'utf-8'});
let passwords = input.split('\n');
passwords.pop();
passwords.pop();
console.log(passwords[passwords.length -1])
let totalCounts = 0;
passwords.forEach((password, i) => {
    const parts = password.split(' ');
    const rule1 = parts[0];
    const rule2 = parts[1].split('')[0];
    console.log(rule2);
    const pass = parts[2];

    const countlimits = rule1.split("-");
    const upper = countlimits[1];
    const lower = countlimits[0];

    console.log('the rules', upper, lower, rule2)

    total = pass.split('').reduce((count, char) => {
        console.log('count char', count, char)
        if (char === rule2) {
            console.log('it matches', char, count);
            return count +=1;
        }
        return count;
    }, 0);
    console.log(pass, total, rule2);

    if(total >= +lower && total <=upper) {
        totalCounts++
    }
})

console.log('totalCounts', totalCounts);
