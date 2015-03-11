autowatch = 1
outlets = 10

function b() //button
{
	var args = arrayfromargs(arguments)
	var buttonNum = args[0]
	var pressed = args[1]
		
	if (buttonNum < 3) {
		outlet(buttonNum, pressed)
	} else if (buttonNum == 8) {
		outlet(8, pressed)
    } else if (pressed) {
		outlet(3, buttonNum - 3)
	}
}

function p() //(soft)pot
{
	var args = arrayfromargs(arguments)
	var potNum = args[0]
	var valStr = args.slice(1,args.length).join("")
	var value = Number(valStr) / 1023.0

	if (!isNaN(value)) {
		outlet(4 + potNum, value)
	}
}

function s() //switch
{
	var args = arrayfromargs(arguments)
	var switchNum = args[0]
	var on = args[1]

	outlet(6 + switchNum, on)
}

function r() //rotary encoder
{
	var args = arrayfromargs(arguments)
	var rotNum = args[0]
	var valStr = args.slice(1,args.length).join("")
	var value = Number(valStr)

	outlet(9, value)
}

function outletComments(num)
{
	assist(num == 0 ? "layering button?"
         : num == 1 ? "freeze button"
         : num == 2 ? "store button"
         : num == 3 ? "preset recall buttons"
		 : num == 8 ? "softpot activator"
		 : num == 9 ? "rotary encoder direction"
         : num <= 5 ? ("softpot " + (num-4) + " value")
		 : ("switch " + (num-6) + " value"))
}

setoutletassist(-1, outletComments)
