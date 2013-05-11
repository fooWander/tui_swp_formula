$(document).ready(function() {
	$('#searchcriteria').focus(function() {
		if (this.value==this.defaultValue) {
			$(this).css('color','#000000');
			this.value='';
		}
	}).blur(function() {
		if (this.value=='') {
			this.value=this.defaultValue;
			$(this).css('color','');
		}
	});
	
	$('#navbar .handle').click(function() {
		var parentNode=$(this).parent();
		var childCount=parentNode.children('a').length;
		
		if(childCount > 1) {	
			if(parentNode.hasClass('sel')) {
				parentNode.css('height',24*childCount+'px');
				parentNode.removeClass('sel');
				parentNode.animate({'height':24}, {duration: 500});
			} else {
				parentNode.css('height','24px');
				parentNode.addClass('sel');
				parentNode.animate({'height':childCount*24}, {duration: 500});
			}
		}
	});
	
	$('#navbar a').hover(function() {
		var bubbleText=$(this).children('em').html();
		if (bubbleText) {
			$('#bubble').hide().html(bubbleText).css({'top':10+$(this).parent().position().top+$(this).position().top+'px', 'left':'200px'}).show().animate({'left':190},{duration:100});
		}
	}, function() {
		$('#bubble').hide();
	});
		
	$('#annoybox img').click(function() {
		document.cookie='w2dannoybox=hide';
		$('#annoybox').animate({'height':0},{duration:300});
	});
	
	$(window).load(function() {
		if (document.cookie.indexOf('w2dannoybox=hide')==-1) {
			$('#annoybox').animate({'height':50},{duration:300});			
		}
	});
});

