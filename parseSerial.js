autowatch = 1
outlets = 5

function b() //button
{
	var args = arrayfromargs(arguments)
	var buttonNum = args[0]
	var pressed = args[1]
	
	buttonNum -= 3 // temporary
	
	if (buttonNum < 2) {
		outlet(buttonNum, pressed)
	} else if (pressed) {
		outlet(2, buttonNum - 1)
	}
}

function p() //(soft)pot
{
	var args = arrayfromargs(arguments)
	var potNum = args[0]
	var valStr = args.slice(1,args.length).join("")
	post(valStr)
	var value = Number(valStr) / 1024.0

	outlet(3 + potNum, value)
}

function outletComments(num)
{
	assist(num == 0 ? "freeze button"
         : num == 1 ? "store button"
         : num == 2 ? "preset recall buttons"
         : ("softpot " + (num-3) + " value"))
}

setoutletassist(-1, outletComments)
