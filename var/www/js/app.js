_.templateSettings = {
  interpolate: /\{\{(.+?)\}\}/g
};

$(function domReady() {
  function detectMediaType(extension) {
    var mediaTypesFromExtension = {
      avi:  'video',
      flac: 'audio',
      flv:  'video',
      jpeg: 'image',
      jpg:  'image',
      m4a:  'audio',
      m4v:  'video',
      mov:  'video',
      mp3:  'audio',
      mp4:  'video',
      mpg:  'video',
      ogg:  'audio',
      ogv:  'video',
      png:  'image',
      webm: 'video'
    };

    return mediaTypesFromExtension[extension];
  }

  function extname(name) {
    var ext = name.match(/\.([a-zA-Z0-9]+)$/);
    return ext && ext[1].toLowerCase();
  }

  function detectIconClass(name) {
    var iconClassFromMediaType = {
      audio: 'icon-headphones',
      image: 'icon-picture',
      video: 'icon-film'
    };

    var mediaType = detectMediaType(extname(name));
    var iconClass = iconClassFromMediaType[mediaType];
    
    return iconClass || 'icon-file';
  }

  function EntryPresenter(entry) {
    var isDirectory = entry.get('isDirectory'),
      name = entry.get('name');

    this.iconClass = isDirectory ? 'icon-folder-close' : detectIconClass(name);
    this.path = entry.get('path');
    this.displayName = name + (isDirectory ? '/' : '');
  }

  var Entry = Backbone.Model.extend({});

  var EntryCollection = Backbone.Collection.extend({
    model: Entry,
    url: function () { return '/cgi-bin/ls?path=' + this.path; }
  });

  var EntryView = Backbone.View.extend({
    template: _.template($('#entry-template').html()),
    events: {
      'click a': 'changeDirectory'
    },
    render: function () {
      var presenter = new EntryPresenter(this.model);
      this.$el.html(this.template(presenter));
      return this;
    },
    changeDirectory: function () {
      if (this.model.get('isDirectory')) {
        app.changeDirectory(this.model.get('path'));
        return false;
      }
    }
  });

  var AppView = Backbone.View.extend({
    el: $('#app'),
    events: {
      'click #up-one-level': 'upOneLevel'
    },
    initialize: function () {
      this.changeDirectory(config.documentRoot);
    },
    changeDirectory: function (path) {
      var self = this;

      this.path = path;
      this.entries = new EntryCollection();
      this.entries.path = this.path; // FIXME: use initialize/get instead

      this.entries.fetch().complete(function() {
        self.render();
      });
    },
    upOneLevel: function () {
      var dirs = this.path.split('/');
      dirs.pop();

      if (1 != dirs.length) {
        this.changeDirectory(dirs.join('/'));
      }
    },
    render: function () {
      var models = this.entries.models;
      var $entryList = this.$("#entry-list");

      $entryList.html('');

      models.forEach(function (entry) {
        var view = new EntryView({ model: entry });
        $entryList.append(view.render().el);
      });

      document.title = this.path;
      $('#path-outlet').html(this.path);
    }
  });

  var app = new AppView();
});
