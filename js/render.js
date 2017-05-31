const canvas = document.querySelector('#canvas');
canvas.width = canvas.offsetWidth; //document.body.offsetWidth;
canvas.height = canvas.offsetHeight; //document.body.offsetHeight;

const ctx = canvas.getContext('2d');
ctx.lineWidth = 1;
ctx.strokeStyle = '#ffffff';

const $fps = document.querySelector('#fps');

let shift = 0.05,
	depth = 12,
	color1 = '#8a5300',
	color2 = '#a0d000',
	color2n = 4,
	strokeCalls = 0,
	drawRecursiveCalls = 0;

const drawRecursive = (i, prevPrevPos, prevPos, prevVec) => {
	drawRecursiveCalls += 1;
	if (i === depth) {
		ctx.stroke();
		strokeCalls += 1;
		ctx.strokeStyle = color2;
		ctx.beginPath();
		return;
	}
	i += 1;

	prevVec.rotateByAngle(shift);
	let next = Geo.getNext(prevPos, prevVec);

	let nextPos = next.pos;

	ctx.moveTo(prevPos.x, prevPos.y);
	ctx.lineTo(nextPos.x, nextPos.y);

	if (i % 2 == 0) {
		ctx.moveTo(prevPrevPos.x, prevPrevPos.y);
		ctx.quadraticCurveTo(prevPos.x, prevPos.y, nextPos.x, nextPos.y);
	}
	if (i == depth - color2n) {
		ctx.strokeStyle = color1;
		ctx.stroke();
		strokeCalls += 1;
		ctx.strokeStyle = color2;
		ctx.beginPath();
	}

	drawRecursive(i, prevPos, nextPos, next.vecL);
	drawRecursive(i, prevPos, nextPos, next.vecR);
};

const render = () => {
	let pos = new Vector(canvas.width / 2, canvas.height+10),
		vec = new Vector(0, -canvas.height * 0.25);

	let timestamp = Date.now();

	ctx.clearRect(0, 0, canvas.width, canvas.height);
	ctx.beginPath();
	ctx.moveTo(pos.x, pos.y);
	drawRecursive(0, null, pos, vec);
	ctx.stroke();

	console.info('rendererd in: ', (Date.now() - timestamp), 'ms');
	console.info('calls to ctx.stroke: ', strokeCalls);
	console.info('calls to drawRecursive: ', drawRecursiveCalls);
	strokeCalls = 0;
	drawRecursiveCalls = 0;
};

render();

let animation = () => {
	animation.x += 1;
	shift = animation.f(animation.x);
	render();

	animation.frameId = window.requestAnimationFrame(animation);
};
animation.x = 0;
animation.f = (x) => Math.sin(x * 0.005) * 0.1;
animation.frameId = null;

let $checkbox = document.querySelector('#animation-checkbox input');
$checkbox.addEventListener('change', (event) => {
	if ($checkbox.checked) {
		animation.frameId = window.requestAnimationFrame(animation);
	} else {
		window.cancelAnimationFrame(animation.frameId);
	}
}, false);
