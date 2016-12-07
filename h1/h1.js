'use strict'
if (process.argv.length < 3) {
  console.log('enter file name as argument')
  process.exit(0)
}

var fs = require('fs')
var input = fs.readFileSync(process.argv[2], 'utf-8')
var numbers = input.split(/[ \n]/).map(Number)
numbers.reverse()
function next () {
  return numbers.pop()
}

var tn = next()
for (var i = 0; i < tn; i++) solve()

function solve () {
  let INF = 1000000000
  let n = next()
  let d = next()
  let input = []
  for (let i = 0; i < n; i++) input.push(next())
  let dp = {}
  dp[input[0]] = 0
  for (let i = 1; i < input.length - 1; i++) {
    let dp2 = {}

    for (let h in dp) {
      for (let j = Number(h) - d; j <= Number(h) + d; j++) {
        if (!dp2[j]) dp2[j] = INF
        let cost = Math.abs(j - input[i])
        dp2[j] = Math.min(dp2[j], dp[h] + cost)
      }
    }
    dp = dp2
  }
  let res = INF
  for (let j = input[n - 1] - d; j <= input[n - 1] + d; j++) {
    if (!dp[j]) continue
    res = Math.min(res, dp[j])
  }
  if (res === INF) res = -1
  console.log(res)
}
