autowatch = 1
inlets = 2
outlets = 1

var curNotes = {}

function list(num)
{
	var note = arrayfromargs(arguments)
	var pitch = note[0]
	var velocity = note[1]
	post("p: " + pitch + " v: " + velocity)


	if (velocity > 0) {
		if (numCurNotes() == 0) {
			outlet(0, "bang")
		} 
		curNotes[pitch] = 1
	} else {
		curNotes[pitch] = 0
	}
}

function numCurNotes()
{
	var cnt = 0
	for (var pitch in curNotes) {
		if (curNotes[pitch] == 1) {
			cnt++
		}
	}
	return cnt
}

function outletComments(num)
{
	assist("bang on first note down after silence")
}

setoutletassist(-1, outletComments)
