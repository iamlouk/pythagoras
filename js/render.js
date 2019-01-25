const canvas = document.querySelector('#canvas')
canvas.width = canvas.offsetWidth
canvas.height = canvas.offsetHeight

const ctx = canvas.getContext('2d')
ctx.lineWidth = 1
ctx.strokeStyle = '#ffffff'

const $fps = document.querySelector('#fps')

let shift = 0.0,
	depth = 14,
	color1 = '#8a5300',
	color2 = '#a0d000',
	color2n = 5,
	fps = 0

const drawRecursive = (i, prevPrevPos, prevPos, prevVec) => {
	if (i === depth) {
		ctx.stroke()
		ctx.strokeStyle = color2
		ctx.beginPath()
		return
	}
	i += 1

	prevVec.rotateByAngle(shift)
	const { pos, vecL, vecR } = getNextBranch(prevPos, prevVec)

	ctx.moveTo(prevPos.x, prevPos.y)
	ctx.lineTo(pos.x, pos.y)

	if (i % 2 == 0) {
		ctx.moveTo(prevPrevPos.x, prevPrevPos.y)
		ctx.quadraticCurveTo(prevPos.x, prevPos.y, pos.x, pos.y)
	}

	if (i == depth - color2n) {
		ctx.strokeStyle = color1
		ctx.stroke()
		ctx.strokeStyle = color2
		ctx.beginPath()
	}

	drawRecursive(i, prevPos, pos, vecL)
	drawRecursive(i, prevPos, pos, vecR)
}

const render = () => {
	const pos = new Vector(canvas.width / 2, canvas.height + 10),
	      vec = new Vector(0, -canvas.height * 0.2)

	// const timestamp = Date.now()

	ctx.clearRect(0, 0, canvas.width, canvas.height)
	ctx.beginPath()
	ctx.moveTo(pos.x, pos.y)
	drawRecursive(0, null, pos, vec)
	ctx.stroke()

	// console.info('rendererd in: ', (Date.now() - timestamp), 'ms')

	fps += 1
};

let animation = () => {
	animation.x += 1
	shift = animation.f(animation.x)
	render()

	animation.frameId = window.requestAnimationFrame(animation)
}
animation.x = 0
animation.f = (x) => Math.sin(x * 0.005) * 0.1
animation.frameId = null

setInterval(() => {
	$fps.innerText = `FPS: ${fps}`
	fps = 0
}, 1000)

const $checkbox = document.querySelector('#animation-checkbox input');
$checkbox.addEventListener('change', event => {
	if ($checkbox.checked) {
		if (animation.frameId != null)
			window.cancelAnimationFrame(animation.frameId)
		animation.frameId = window.requestAnimationFrame(animation)
	} else {
		window.cancelAnimationFrame(animation.frameId)
		animation.frameId = null
	}
}, false)

if ($checkbox.checked)
	animation.frameId = window.requestAnimationFrame(animation)
else
	render()
