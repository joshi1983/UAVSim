class Player extends EventDispatcher {
	constructor(project, virtualAnimationStateKeys) {
		super();
		if (!(project instanceof Project))
			throw new Error('Project required');
		if (!(virtualAnimationStateKeys instanceof VirtualAnimationStateKeys))
			throw new Error('virtualAnimationStateKeys required');

		this.virtualAnimationStateKeys = virtualAnimationStateKeys;
		this.project = project;
		this.time = 0;
		this.startPlayingTime = undefined;
		this.timeDisplay = document.getElementById('player-time');
		const playStopButton = document.getElementById('player-play-stop');
		const pauseButton = document.getElementById('player-pause');
		const continuePlayingIntervalMS = 20;
		const outer = this;
		this.timer = undefined;
		this.canPlayAudio = false;

		/*
		Need to convert mp3 URL to data URL to control currentTime when hosted by UAVSim.
		Some articles suggest the server can be configured better for this to not be necessary 
		but this is a simple workaround.
		*/
		urlToDataURL('/animationStudio/audio/audio.mp3').then(function(dataUrl) {
			outer.audio = new Audio();
			outer.audio.src = dataUrl;
			outer.audio.addEventListener("canplay", evt => { 
				outer.canPlayAudio = true;
			});
		});
		
		function pauseAudio() {
			if (outer.canPlayAudio)
				outer.audio.pause();
		}

		function stopPlaying() {
			pauseButton.setAttribute('disabled', true);
			clearTimeout(outer.timer);
			outer.setTimeMilliseconds(0);
			playStopButton.innerText = 'Play';
			outer.timer = undefined;
			pauseAudio();
		}

		function getNow() {
			return new Date().getTime();
		}

		function continuePlaying() {
			outer.setTimeMilliseconds(getNow() - outer.startPlayingTime);
			if (outer.time * 0.001 > project.getDurationSeconds()) {
				stopPlaying();
				return;
			}
			outer._dispatchEvent({'key': 'player-time-changed'});
			outer.sendCSVStateToServer().then(function() {
				// check that this wasn't stopped or paused while processing an HTTP request.
				if (outer.timer !== undefined)
					outer.timer = setTimeout(continuePlaying, continuePlayingIntervalMS);
			});
		}

		function startPlaying() {
			playStopButton.innerText = 'Stop';
			outer.startPlayingTime = new Date().getTime() - outer.time;
			outer.timer = setTimeout(continuePlaying, 0);
			pauseButton.removeAttribute('disabled');
			if (outer.canPlayAudio) {
				const timeSeconds = outer.time * 0.001;
				if (!isNaN(timeSeconds) && timeSeconds >= 0) {
					outer.audio.currentTime = timeSeconds;
					outer.audio.play();
				}
			}
		}
		this.setTimeMilliseconds(0);
		playStopButton.addEventListener('click', function() {
			if (outer.timer === undefined)
				startPlaying();
			else
				stopPlaying();
		});
		pauseButton.addEventListener('click', function() {
			playStopButton.innerText = 'Play';
			pauseButton.setAttribute('disabled', true);
			clearTimeout(outer.timer);
			outer.timer = undefined;
			pauseAudio();
		});
	}

	getFormattedTime(timeSeconds) {
		const isNegative = timeSeconds < 0;
		timeSeconds = Math.abs(timeSeconds);
		const minutes = Math.floor(timeSeconds / 60);
		var seconds = '' + Math.floor(timeSeconds % 60);
		while (seconds.length < 2)
			seconds = '0' + seconds;
		const fraction = (timeSeconds % 1).toFixed(2).substring(1);
		const sign = isNegative ? '-' : '';
		return sign + minutes + ':' + seconds + fraction;
	}

	setTimeMilliseconds(timeMilliseconds) {
		if (typeof timeMilliseconds !== 'number' || isNaN(timeMilliseconds))
			throw new Error('setTimeMilliseconds requires time as a number.');
		this.time = timeMilliseconds;
		this.timeDisplay.innerText = this.getFormattedTime(this.time * 0.001);
	}

	setTimeSeconds(seconds) {
		this.setTimeMilliseconds(seconds * 1000);
	}

	getTimeSeconds() {
		return this.time * 0.001;
	}

	sendCSVStateToServer() {
		const animationState = {};
		const keys = this.virtualAnimationStateKeys.getAllSourceKeys(this.project);
		const outer = this;
		keys.forEach(function(sourceKey) {
			const virtualKeyString = outer.virtualAnimationStateKeys.getVirtualKeyFor(sourceKey);
			const val = outer.project.getValue(virtualKeyString, outer.time * 0.001);
			animationState[sourceKey] = outer.virtualAnimationStateKeys.convertNumberToSourceType(sourceKey, val);
		});
		return fetch('/api/csv-inputs', {
			'method': 'POST',
			'body': JSON.stringify(animationState)
		});
	}

	isPlaying() {
		return this.timer !== undefined;
	}
}