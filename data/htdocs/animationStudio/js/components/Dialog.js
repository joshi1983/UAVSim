class Dialog {
	constructor(dialogElementId) {
		this.dialogElement = document.getElementById('data-point-details');
		this.dialogElement.classList.add('dialog');
	}

	hide() {
		this.dialogElement.classList.remove('showing');
		this.backdrop.remove();
	}

	show() {
		this.backdrop = document.createElement('div');
		this.backdrop.setAttribute('class', 'dialog-backdrop');
		document.body.appendChild(this.backdrop);
		this.dialogElement.classList.add('showing');
		const outer = this;
		this.backdrop.addEventListener('click', function() {
			outer.hide();
		});
	}
}