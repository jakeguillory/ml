SUBDIRS = lib linear_reg perceptron

.PHONY: all clean debug release

all: release

release:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir MODE=release; \
	done

debug:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir MODE=debug; \
	done

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done

